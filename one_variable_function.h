//
// Created by Persist on 3/5/24.
//

#ifndef EULER_METHOD_ONE_VARIABLE_FUNCTION_H
#define EULER_METHOD_ONE_VARIABLE_FUNCTION_H

//Input one variable functoin, like y = sin(x).
double one_variable_function(double x) {
    return pow(x, 2) - 2*x - 8;
}

void origin_function_one(sf::RenderWindow& window, sf::VertexArray& graph, double size, double one_variable_input_function(double), double start, double end) {
    graph.clear();
    for (double x = start/size; x <= end/size; x += 0.001) {
        double y = one_variable_input_function(x);
        graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Blue));
    }
    window.draw(graph);
}

#endif //EULER_METHOD_ONE_VARIABLE_FUNCTION_H
