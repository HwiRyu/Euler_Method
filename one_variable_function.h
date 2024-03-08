//
// Created by Persist on 3/5/24.
//

#ifndef EULER_METHOD_ONE_VARIABLE_FUNCTION_H
#define EULER_METHOD_ONE_VARIABLE_FUNCTION_H

//Input one variable functoin, like y = sin(x).
double one_variable_function(double x) {
    return 0;
}

void origin_function_one(sf::RenderWindow& window, sf::VertexArray& graph, double size, double one_variable_input_function(double), double start, double end) {
    graph.clear();
    for (double x = start/size; x <= end/size; x += 0.001) {
        double y = one_variable_input_function(x);
        graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Blue));
    }
    window.draw(graph);
}

//Input one variable functoin, like y = sin(x).
double initial_one_variable_function(double x, double initial_x, double initial_y, int number) {
    double y;
    double c1, c2, c3, c4,c5,c6,c7,c8;
    switch (number) {
        case 1:
            c1 = initial_y/exp(initial_x);
            y = c1 * exp(x);
            break;
        case 2:
            c2 = initial_y - pow(initial_x,2)/2;
            y =0.5*x*x + c2;
            break;
        case 3:
            c3 = exp(initial_x) * (1/initial_y - 1);
            y = exp(x) / (c3 + exp(x));
            break;
//        case 4:
//            y = exp(1/y);
//            break;
//        case 5:
//            y = exp(-x*x);
//            break;
        case 6:
            c6 = initial_y / exp(atan(initial_x));
            y = c6 * exp(atan(x));
            break;
//        case 7:
//            y = exp(sin(x));
//            break;
//        case 8:
//            y = 1 / (1+y*y*y);
//            break;
    }
    return y;
}

void initial_origin_function_one(sf::RenderWindow& window, sf::VertexArray& graph, double size,
                                 double initial_one_variable_input_function(double, double, double, int), double start, double end,
                                 double initial_x, double initial_y, int number) {
    graph.clear();
    for (double x = initial_x; x <= end/size; x += 0.001) {
        double y = initial_one_variable_input_function(x, initial_x, initial_y, number);
        graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Blue));
    }
    window.draw(graph);
}


#endif //EULER_METHOD_ONE_VARIABLE_FUNCTION_H
