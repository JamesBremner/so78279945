
#include <wex.h>
#include "plot2d.h"
#include "cStarterGUI.h"

/*

[min thickness, max thickness, min width, max width,
0.017, 0.0179, 32, 59,
0.018, 0.0209, 32, 64,
0.021, 0.0599, 32, 72,
0.060, 0.0669, 32, 70]

*/

struct sData
{
    std::vector<double> minWidth{32, 32, 32, 32};
    std::vector<double> maxWidth{59, 64, 72, 70};

    std::vector<double> minWidthInterp;
    std::vector<double> maxWidthInterp;

    // interpolate data
    void interp();

} theData;

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500})
    {
        // construct plot to be drawn on form
        wex::plot::plot &thePlot = wex::maker::make<wex::plot::plot>(fm);
        thePlot.move({30, 30, 1200, 600});

        // handle draw event
        fm.events().draw(
            [&](PAINTSTRUCT &ps)
            {
                // display the axis
                thePlot.update();

                // construct polygon around possible ranges
                std::vector<int> poly;
                double xoff = 0.003;
                poly.push_back(thePlot.xuser2pixel( 0.017+xoff));
                poly.push_back(thePlot.yuser2pixel( theData.minWidth[0]-5));
                poly.push_back(thePlot.xuser2pixel( 0.017+xoff));
                poly.push_back(thePlot.yuser2pixel( theData.maxWidth[0]-5));
                poly.push_back(thePlot.xuser2pixel( 0.018+xoff));
                poly.push_back(thePlot.yuser2pixel( theData.maxWidth[1]-5));
                poly.push_back(thePlot.xuser2pixel( 0.021+xoff));
                poly.push_back(thePlot.yuser2pixel( theData.maxWidth[2]-5));
                poly.push_back(thePlot.xuser2pixel( 0.060+xoff));
                poly.push_back(thePlot.yuser2pixel( theData.maxWidth[3]-5));
                poly.push_back(thePlot.xuser2pixel( 0.060+xoff));
                poly.push_back(thePlot.yuser2pixel( theData.minWidth[3]-5));

                wex::shapes S(ps);
                S.fill();
                S.color(0x00FF00);
                S.polygon( poly );
            });

        // resize plot when form resizes
        fm.events().resize(
            [&](int w, int h)
            {
                thePlot.move({30, 30, w, h});
                thePlot.update();
            });

        // construct a plot traces
        wex::plot::trace &t1 = thePlot.AddStaticTrace();

        thePlot.XUValues(0.017, 0.001);
        thePlot.setFixedScale(0.0, 0.08, 20, 80);

        show();
        run();
    }

private:
};

main()
{
    cGUI theGUI;
    return 0;
}
