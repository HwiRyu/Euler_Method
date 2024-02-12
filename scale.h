//
// Created by Persist on 2/3/24.
//

#ifndef PICARD_ITERATION_SCALE_H
#define PICARD_ITERATION_SCALE_H

double x_scale (double x, double size) {
    return x * size;
}
double y_scale (double y, double size) {
    return -y * size;
}

#endif //PICARD_ITERATION_SCALE_H
