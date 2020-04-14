// std includes
#include <iostream>
#include <string>
// Qt includes
#include <QApplication>
#include "env/gui/MainWindow.h"
#include "env/simulation/Simulation.h"
#include "env/interface/Interface.h"
#include "QTable.h"
#include <thread>
#include <chrono>

int game(int argc, char *argv[]);

void learn(
        bool loadQTable,
        Simulation &sim,
        Interface &interface,
        QApplication &application,
        MainWindow &window,
        float timeStep,
        int discreteOSSize,
        bool &exitFlag
);


template <class T>
void printArray(T t) {
    for(auto e : t) {
        std::cout << e << '\n';
    }
}

float randomFloat() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int randomInt(int min, int max) {
    return rand()%(max-min + 1) + min;
}

int main(int argc, char *argv[]) {
    constexpr int discreteOSSize {20};
    constexpr bool wind = true;
    Simulation sim = Simulation(-10.0f, wind);
    auto interface = Interface(sim, discreteOSSize);

    QApplication app{argc, argv};
    MainWindow w{sim.getWorldWidth(),sim.getWorldHeight(), 10, interface}; // MPR = meters to pixels ratio
    w.createGround(-sim.getGround().getYPos(), sim.getGround().getWidth());
    w.createRocket(0, 0, sim.getRocket().getVertices());
    w.show();

    float timeStep = 1.0f / 60.0f;

    // todo: refactor and improve the following horrible memory mess. Use smart pointers.
    bool exitFlag = false;
    std::unique_ptr<std::thread> threadObj {
        new std::thread(
                learn,
                false,
                std::ref(sim),
                std::ref(interface),
                std::ref(app),
                std::ref(w),
                timeStep,
                discreteOSSize,
                std::ref(exitFlag))
    };
    int ret = app.exec();
    exitFlag = true;
    if(threadObj->joinable()) {
        threadObj->join();
    }
    return ret;
}

void learn(
        bool loadQTable,
        Simulation &sim,
        Interface &interface,
        QApplication &application,
        MainWindow &window, float timeStep,
        int discreteOSSize,
        bool &exitFlag) {

    constexpr float learningRate {0.1f};
    constexpr float discount {0.95f};
    constexpr int episodes {1000000};
    float epsilon {0.20f};
    constexpr int startEpsilonDecaying {1};
    const int endEpsilonDecaying {episodes/2};
    float epsilonDecayValue = epsilon/(endEpsilonDecaying - startEpsilonDecaying);
    constexpr int movePenalty {1};
    constexpr int crashPenalty {300};
    constexpr int landReward {10};

    constexpr int showEvery {100000};

    int xPosDiscreteOSSize {discreteOSSize};
    int yPosDiscreteOSSize {discreteOSSize};
    int angleDiscreteOSSize {discreteOSSize};
    int linearVelocityOSSize {discreteOSSize};
    int angularVelocityOSSize {discreteOSSize};

    QTable startQTable(std::vector<int> {
        xPosDiscreteOSSize,
        yPosDiscreteOSSize,
        angleDiscreteOSSize,
        linearVelocityOSSize,
        angularVelocityOSSize,
        interface.actionSpaceCount()
    });

    if(!loadQTable) {
        // init startQTable with random values
        startQTable.randomFill();
    }

    interface.reset();
    datastructs::discreteState discreteState {interface.discreteState()};

    std::vector<int> episodeRewards{};

    for(int episode = 0; episode < episodes; ++episode) {
        bool render {false};
        if(episode % showEvery == 0) {
            render = true;
        }
        bool done = false;
        interface.reset();
        for(int currentStep = 0; currentStep < 600; ++currentStep) {

            std::vector<float> actions{
                    startQTable.getRow(
                            std::vector<int>{
                                    discreteState.xPosition,
                                    discreteState.yPosition,
                                    discreteState.angle,
                                    discreteState.linearVelocity,
                                    discreteState.angularVelocity
                            }
                    )
            };

            int action;
            if(randomFloat() > epsilon) {
                action = static_cast<int>(std::max_element(actions.begin(),actions.end()) - actions.begin());
            } else {
                action = randomInt(0, interface.actionSpaceCount()-1);
            }

            interface.step(action); // optimise this
            if(render) {
                sim.updateGraphics(application, window, timeStep);
            }
            float reward {interface.reward()};
            if(reward == landReward) {
                done = true;
            }
            datastructs::discreteState newDiscreteState {interface.discreteState()};
            if(!done) {
                float maxFutureQ {startQTable.maxFutureQ(std::vector<int>{newDiscreteState.xPosition, newDiscreteState.yPosition, newDiscreteState.angle, newDiscreteState.linearVelocity, newDiscreteState.angularVelocity})};
                float currentQ {startQTable.get(std::vector<int>{discreteState.xPosition, discreteState.yPosition, discreteState.angle, discreteState.linearVelocity, discreteState.angularVelocity, action})};
                float newQ {(1 - learningRate) * currentQ + learningRate * (reward + discount * maxFutureQ)};
                startQTable.update(std::vector<int>{discreteState.xPosition, discreteState.yPosition, discreteState.angle, discreteState.linearVelocity, discreteState.angularVelocity, action}, newQ);
            } else {
                startQTable.update(std::vector<int>{discreteState.xPosition, discreteState.yPosition, discreteState.angle, discreteState.linearVelocity, discreteState.angularVelocity, action}, landReward);
            }
            discreteState = newDiscreteState;
        }

        if(done) {
            std::cout << "It landed on " << episode << '\n';
        } else if(episode % 200 == 0) {
            std::cout << "Episode: " << episode << '\n';
        }

        if(endEpsilonDecaying >= episode >= startEpsilonDecaying) {
            epsilon -= epsilonDecayValue;
        }
    }
}

int game(int argc, char *argv[]) {
    constexpr bool wind = true;
    Simulation sim = Simulation{-10.0f, wind};
    auto interface = Interface(sim, 60);

    QApplication app{argc, argv};
    MainWindow w{sim.getWorldWidth(),sim.getWorldHeight(), 10, interface}; // MPR = meters to pixels ratio

    w.createGround(-sim.getGround().getYPos(), sim.getGround().getWidth());
    w.createRocket(0, 0, sim.getRocket().getVertices());
    w.show();

    // todo: refactor and improve the following horrible memory mess. Use smart pointers.
    bool exitFlag = false;
    std::thread* simThread {sim.run(app, w, exitFlag)};
    int ret = app.exec();
    exitFlag = true;
    if(simThread->joinable()) {
        simThread->join();
    }
    delete simThread;
    return ret;
}
