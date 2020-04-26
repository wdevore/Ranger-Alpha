//
// Created by William DeVore on 3/28/16.
//

#ifndef RANGERBETA_SCENE_MANAGER_H
#define RANGERBETA_SCENE_MANAGER_H

#include <stack>
#include "../ranger.h"

namespace Ranger {
    /*!
     * The [SceneManager] manages [Scene]s. Some [Scene]s are transient
     * while others are permanent during the life of the game.
     * For example, the splash screen is transient. There is no reason to
     * keep the splash screen [Scene] when it is only seen once during the
     * life of the game.
     *
     * The [SceneManager] is a "System" in and of itself. The [Engine] calls the
     * [SceneManager.step] method.
     * [step] then visits the current running [Scene] where visibility
     * and rendering can occur.
     */
    class SceneManager final {
    public:
        void end();

        /*!
         * If there are no more [Scene]s to draw [step] returns false
         * indicating the Engine core should begin shutting down.
         */
        bool step();

        void setNextScene();

        /*!
         * Pop off a [Scene] from the queue.
         * This [Scene] will replace the running one.
         * The running [Scene] will be deleted.
         * If there are no more [Scene]s in the stack the execution is terminated.
         * ONLY call it if there is a running scene.
         */
        void pop();

        /*!
         * Suspends the execution of the running [Scene],
         * pushing it on the stack of suspended [Scene]s.
         * The new [scene] will be executed.
         */
        void push(const BaseNodeSPtr& scene);

        /*!
         * Replaces the running [Scene] with a new one.
         * The running [Scene] is terminated.
         * ONLY call it if there is a running [Scene].
         */
        void replace(const BaseNodeSPtr& scene);

        /*!
         * Pops off all [Scene]s from the queue until the root/bottom
         * [Scene] in the queue.
         */
        void popToRoot();

        /*!
         * Pops off all [Scene]s from the queue until it reaches [level].
         * The [level] is zero based. If there are 4 scenes then scene 4
         * is at [level] 3.
         *     levels:
         *     N   <--- Stack top, currently running scene
         *     ...
         *     3
         *     2
         *     1
         *     0   <---- Root scene
         *
         * If [level] is [ALL], it will effectively end/stop the [SceneManager].
         * If [level] is [TO_ROOT], it will pop all [Scene]s until it reaches to root [Scene].
         * If [level] is >= than stack top, nothing is done.
         */
        void popToStackLevel(int level);

    private:
        struct STACK {
            static constexpr int TO_ROOT = 0;
            static constexpr int ALL = 1;
        };

        struct SCENE_STATE {
            static constexpr int ENTER = 0;
            static constexpr int ENTERING = 1;
            static constexpr int ENTER_COMPLETE = 2;
            static constexpr int EXIT = 3;
            static constexpr int EXITING = 4;
            static constexpr int EXIT_COMPLETE = 5;
        };

        std::stack<BaseNodeSPtr> _scenes;

        BaseNodeSPtr _runningScene;
        BaseNodeSPtr _nextScene;

        bool _ignoreClear{false};

        bool _warned{false};

        /**
         * Whether or not the replaced [Scene] will be cleaned up.
         * A Scene is "not cleaned up" by default when it is popped or replaced on
         * the stack. A Scene must explicitly request that it IS cleaned
         * prior to being popped or replaced using the _autoClean flag.
         */
//        bool _cleanup{false};
        void popTotackLevel(int level);
    };
}

#endif //RANGERBETA_SCENE_MANAGER_H
