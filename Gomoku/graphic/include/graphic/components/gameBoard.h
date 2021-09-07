#pragma once
#include <graphic/components/view.h>
#include <functional>
#include <vector>

namespace grc
{
    class gameBoard : public grc::view
    {
    private:
        std::vector<std::vector<int>> boardState;
        std::vector<grc::point> point;
        /**
         * @brief 
         * 게임 모드 타입 !
         * 0 : 일반 게임 모드
         * 1 : AI 추적 모드
         */
        int mode = 0;

        /**
         * @brief 
         * 0 : 흑 차례
         * 1 : 백 차례
         */
        int color = 0;

    public:
        int counting = 0;
        gameBoard(grc::rect f, grc::size bsize) : grc::view(f, grc::color(0x854b25ff)), boardSize(bsize)
        {
            for (int i = 0; i < boardSize.height; i++)
            {
                boardState.push_back(std::vector<int>(boardSize.width, 0));
            }
        }

        std::function<void(std::vector<grc::point> *state)> boardChanged;

        bool setState(grc::point pos, int state);
        bool setPredict(grc::point pos, int state, int text = 0);

        grc::size boardSize;
        grc::color lineColor = grc::color(0x36210fff);
        grc::color blackColor = grc::color(0x2f2f2fff);
        grc::color whiteColor = grc::color(0xdcdcdcff);
        grc::color predictColor = grc::color(0x0563ffff);

        // virtual int click(int state, int x, int y) override;
        virtual bool render() const override;
        virtual int click(int state, int x, int y) override;

        void clear(int mode = 0);

    protected:
    };
}