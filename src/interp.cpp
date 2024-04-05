
void sData::interp()
{
    minWidthInterp.push_back(minWidth[0]);
    maxWidthInterp.push_back(maxWidth[0]);

    minWidthInterp.push_back(minWidth[0]);
    maxWidthInterp.push_back(maxWidth[1]);

    double f = (maxWidth[2] - maxWidth[1]) / (0.021 - 0.018);

    minWidthInterp.push_back(minWidth[0]);
    maxWidthInterp.push_back(maxWidth[1] + f * (0.019 - 0.018));
    minWidthInterp.push_back(minWidth[0]);
    maxWidthInterp.push_back(maxWidth[1] + f * (0.020 - 0.018));

    minWidthInterp.push_back(minWidth[0]);
    maxWidthInterp.push_back(maxWidth[2]);

    f = (maxWidth[3] - maxWidth[2]) / (0.07 - 0.021);

    for (int x = 22; x <= 60; x++)
    {
        double xv = x / 1000.0;
        double yv = maxWidth[2] + f * (xv - 0.021);
        minWidthInterp.push_back(minWidth[0]);
        maxWidthInterp.push_back(yv);
    }
}