//
// Created by Persist on 3/5/24.
//

#ifndef EULER_METHOD_PARAMETER_FUNCTION_H
#define EULER_METHOD_PARAMETER_FUNCTION_H



struct Point {
    double x;
    double y;
};

//Input parameter function, like x = f(t), y = g(t).
Point parameter_function(double t) {
    Point output;
    output.x =
            sin(4*t) * (std::exp(cos(1/2*t)) - 2 * cos(18*t) - pow(sin(1/12), 5));
    output.y =
            cos(5*t) * (std::exp(cos(1/3*t)) - 2 * cos(11*t) - pow(sin(1/12), 5));
    return output;
}

double origin_function_parameter(sf::RenderWindow& window, sf::VertexArray& graph, double size,
                                 Point (*parameter_input_function)(double), double current_t_value,
                                 double point_x, double point_y) {
    graph.clear();
    Point p;
    double x, y;
    double t_start = 0;
    double t_end = 0;
    double output = -100000000;
    bool click = false;
    std::vector<double> click_t;

    sf::CircleShape circle(std::max(size/20.0, 3.0)); // Create a circle with radius 3 (adjust as needed)
    circle.setFillColor(sf::Color::Black);

    for (double t = t_start; t <= t_end; t += 0.001){
        p = parameter_input_function(t);
        x = p.x;
        y = p.y;

        if (abs(point_x - x) < 5/size && abs(point_y - y) < 5/size) {
            click_t.push_back(t);
            click = true;
        }

        if (abs(current_t_value - t) <= 0.001)
            circle.setPosition(sf::Vector2f(x_scale(x, size)-circle.getRadius(), y_scale(y, size)-circle.getRadius())); // Set position based on scaled coordinates
        else
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Green));
    }
    window.draw(graph);
    window.draw(circle); // Draw the circle
    if (click) {
        auto minElementIterator = std::min_element(click_t.begin(), click_t.end());
        output = static_cast<double>(*minElementIterator);
    }
    return output;
}

#endif //EULER_METHOD_PARAMETER_FUNCTION_H
