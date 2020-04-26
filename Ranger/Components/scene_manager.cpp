//
// Created by William DeVore on 3/28/16.
//

#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>
#include <sstream>

#include "scene_manager.h"
#include "transition_scene.h"
#include "../Components/Nodes/basenode.h"

namespace Ranger {
    bool SceneManager::step() {
        if (_scenes.empty() && !_warned) {
            std::cerr << __FILE__ <<  " no more scenes to visit." << std::endl;
            _warned = true;
            return false;
        }

        // If there is a Layer that fills the area then _ignoreClear should
        // be set to true.
        if (!_ignoreClear) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// | GL_STENCIL_BUFFER_BIT);
        }

        if (_nextScene)
            setNextScene();

        // TODO Comment out for RELEASE mode
        //Application.instance.objectsDrawn = 0;

        // Visit the Scene's nodes.
        if (_runningScene) {
        //    _runningScene->visit();
        //    _runningScene->visitComplete();
        }

        return true;  // continue to draw
    }

    void SceneManager::setNextScene() {
        // Capture currently running scene type.
        std::cout << "typeid of _runningScene: " << typeid(_runningScene.get()).name() << std::endl;
//        std::cout << "typeid of TransitionScene: " << typeid(TransitionScene).name() << std::endl;
        bool runningSceneIsTransition = typeid(_runningScene.get()) == typeid(TransitionScene);
//
        if (typeid(_nextScene.get()) != typeid(TransitionScene)) {
//            if (_runningScene) {
//                std::cout << "SceneManager::setNextScene: " << "exiting " << _runningScene->toString() << std::endl;
//                _runningScene->onExitTransition();
//                _runningScene->onExit();
//            }
//
//            if (_sendCleanupToScene && _runningScene) {
//                std::cout << "SceneManager::setNextScene: " << "** clearn up ** " << _runningScene->toString() << std::endl;
//                _runningScene->clean(_sendCleanupToScene);
//            }
        }

        _runningScene = _nextScene;
//        std::cout << "SceneManager::setNextScene: " << "next running scene: " << _runningScene->toString() << std::endl;

        _nextScene = nullptr;

//        // Are we transitioning from one Scene to the next.
//        if (!runningSceneIsTransition && _runningScene) {
//            std::cout << "SceneManager::setNextScene: " << "next scene is NOT a transition: " << _runningScene->toString() << std::endl;
//            _runningScene->onEnter();
//            _runningScene->onEnterTransition();
//        }
    }

    void SceneManager::pop() {
        if (!_runningScene) {
            std::cerr << __FILE__ << "::" << __FUNCTION__ << ": there is no running scene." << std::endl;
            return;
        }

        if (_scenes.empty()) {
            // No more Scenes to run.
            std::cerr << __FILE__ << "::" << __FUNCTION__ << ": there are no scenes to pop." << std::endl;
        }
        else {
            // Allow running scene a chance to cleanup.
//            _sendCleanupToScene = true;

            _scenes.pop();

            // If that was the last scene then set the next scene to run as the top.
            if (!_scenes.empty()) {
                _nextScene = _scenes.top();
            }
        }
    }

    void SceneManager::push(const BaseNodeSPtr &scene) {
        if (!scene) {
            std::stringstream ss;
            ss << __FILE__ << "::" << __FUNCTION__ << ": Scene not supplied." << std::endl;
            throw std::invalid_argument(ss.str());
        }

//        _sendCleanupToScene = false;

        //if (_scenes.length > 0)
        //  print("SceneManager.pushScene pushing scene: ${scene} above ${_scenes.first}");
        //else
        //  print("SceneManager.pushScene pushing ${scene} as first scene");

        _scenes.push(scene);
        _nextScene = scene;
        //print("SceneManager.pushScene " + this.toString());
    }

    void SceneManager::replace(const BaseNodeSPtr &scene) {
        if (!_runningScene) {
            std::stringstream ss;
            ss << __FILE__ << "::" << __FUNCTION__ << ": Use runWithScene instead to start the SceneManager." <<
            std::endl;
            throw std::logic_error(ss.str());
        }

        if (!scene) {
            std::stringstream ss;
            ss << __FILE__ << "::" << __FUNCTION__ << ": scene should not be null." << std::endl;
            throw std::logic_error(ss.str());
        }

        if (_scenes.empty()) {
            //print("SceneManager.replaceScene adding ${scene} as first scene");
            _scenes.push(scene);
        } else {
            _scenes.pop();
            //print("SceneManager.replaceScene replacing ${firstScene} with ${scene}");
            _scenes.push(scene);
        }

        _nextScene = scene;
//        _sendCleanupToScene = true;
        //print("SceneManager.replaceScene " + this.toString());
    }

    void SceneManager::popToRoot() {
        popToStackLevel(STACK::TO_ROOT);
    }

    void SceneManager::popToStackLevel(int level) {
        if (!_runningScene) {
            std::stringstream ss;
            ss << __FILE__ << "::" << __FUNCTION__ << ": No running scene." << std::endl;
            throw std::logic_error(ss.str());
        }

        if (_scenes.empty())
            return;

        int seaLevel = _scenes.size();

        if (level >= seaLevel - 1) {
            // Nothing to do. The level is already at the top.
            return;
        }

        int newStackTopLevel;

        if (level == STACK::ALL) {
            // Remove all scenes
            newStackTopLevel = 0;
            level = seaLevel;
        }
        else {
            newStackTopLevel = level + 1;
            level = seaLevel;
        }

        while (level > newStackTopLevel) {
            BaseNodeSPtr current = _scenes.top();
            _scenes.pop();
            if (current->running()) {
                current->onExitTransition();
                current->onExit();
            }
            current->clean();
            level--;
        }

        if (!_scenes.empty())
            _nextScene = _scenes.top();

//        _sendCleanupToScene = false;
    }

    void SceneManager::end() {
        std::cout << "SceneManager: " << "ending." << std::endl;
        popToStackLevel(STACK::ALL);
    }

}