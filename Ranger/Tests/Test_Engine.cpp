//
// Created by William DeVore on 10/22/17.
//
#include <iostream> // For: std

#include "../ranger.h"
#include "Test_Engine.h"

void configureCompleted(Ranger::Engine& engine)
{
    using namespace std;
    cout << "Test_Engine: preConfiguring" << endl;

    engine.start();
}

void Test_Engine::test()
{
    using namespace std;
    cout << "Engine test" << endl;

    using namespace Ranger;
    const EnginePtr& engine = App::engine();

    try {
        engine->configure(configureCompleted);

        // engine->start([](Ranger::Engine& engine) {
        //     using namespace std;
        //     cout << "Test_Engine: preConfiguring" << endl;

        //     engine.configureComplete();
        // });
    } catch (const std::invalid_argument& ex) {
        std::cerr << "invalid_argument caught: " << ex.what() << std::endl;
    } catch (const std::logic_error& ex) {
        std::cerr << "logic_error caught: " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
    }
}