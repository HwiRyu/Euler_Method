#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "scale.h"
#include "euler_method.h"
#include "parameter_function.h"
#include "one_variable_function.h"

int main() {
    // Window initial setting-------------------------------------------------------
    const int width = 1200;
    const int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "Graph Drawing");
    sf::VertexArray EulerGraph(sf::LineStrip);
    sf::VertexArray origin(sf::LineStrip);
    sf::VertexArray parameter(sf::LineStrip);
    sf::VertexArray parameter_point(sf::LineStrip);
    sf::VertexArray initial_origin_graph(sf::LineStrip);


    sf::Font font;
    if (!font.loadFromFile("/System/Library/Fonts/Monaco.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::View graphView(sf::FloatRect(-600.0f, -400.0f, 1200.0f, 800.0f));
    window.setView(graphView);

    sf::Text stepSizeText("", font, 12);
    stepSizeText.setPosition(300, -388);
    stepSizeText.setFillColor(sf::Color::Black);

    sf::Text initial_point("", font, 12);
    initial_point.setPosition(300, -400);
    initial_point.setFillColor(sf::Color::Black);

    sf::Text tracer_on("", font, 12);
    tracer_on.setPosition(300, -364);
    tracer_on.setFillColor(sf::Color::Black);

    sf::Text current_t_value("", font, 12);
    current_t_value.setPosition(300, -376);
    current_t_value.setFillColor(sf::Color::Black);

    sf::Text error("", font, 12);
    error.setPosition(300, -352);
    error.setFillColor(sf::Color::Black);

    sf::Text error_size("", font, 12);
    error_size.setPosition(300, -338);
    error_size.setFillColor(sf::Color::Black);


    //-----------------------------------------------------------------------------

    //Initialize
    double startX = 0;
    double startY = 0;
    double size = 30;
    double step = 1;
    double stepSize = 2;  // Initialize stepSize
    bool tracer = false;
    double t_value = 0;
    sf::Clock clock;
    sf::Clock clock_t;
    int number = 1;
    bool calcul = true;
    double upperbound_error = 0;

    sf::Time lastClickTime = sf::Time::Zero;
    sf::Vector2i lastMousePos; // 마지막 마우스 위치 저장
    sf::Vector2f startPoint; // 초기 클릭 위치 저장
    sf::Time elapsedTime;
    bool increaseValue = false;

    // Main loop
    while (window.isOpen()) {
        elapsedTime = clock_t.getElapsedTime();
        if (increaseValue && elapsedTime.asSeconds() >= 0.001f) {
            t_value += 0.001f;
            clock_t.restart();
        }


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            //In euler_method, control step size.
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Num1:
                        number = 1;
                        break;
                    case sf::Keyboard::Num2:
                        number = 2;
                        break;
                    case sf::Keyboard::Num3:
                        number = 3;
                        break;
                    case sf::Keyboard::Num4:
                        number = 4;
                        break;
                    case sf::Keyboard::Num5:
                        number = 5;
                        break;
                    case sf::Keyboard::Num6:
                        number = 6;
                        break;
                    case sf::Keyboard::Num7:
                        number = 7;
                        break;
                    case sf::Keyboard::Num8:
                        number = 8;
                        break;
                    case sf::Keyboard::U:
                        if (calcul)
                            calcul = false;
                        else
                            calcul = true;
                        break;
                    case sf::Keyboard::A:
                        step -= 0.1;
                        break;
                    case sf::Keyboard::D:
                        step += 0.1;
                        break;
                    case sf::Keyboard::W:
                        if (!tracer)
                            size += 5;
                        break;
                    case sf::Keyboard::S:
                        if (!tracer)
                            size -= 5;
                        break;
                    case sf::Keyboard::T:
                        tracer = !tracer;  // Toggle tracer when 'T' is pressed
                        break;
                    case sf::Keyboard::Q:
                        if (!tracer)
                            t_value -= 0.01;
                        break;
                    case sf::Keyboard::E:
                        if (!tracer)
                            t_value += 0.01;
                        break;
                    case sf::Keyboard::R:
                        //Initialize
                        startX = 0;
                        startY = 0;
                        size = 30;
                        step = 1;
                        stepSize = 2;  // Initialize stepSize
                        tracer = false;
                        t_value = 0;
                        increaseValue = true;
                        window.display();

                        window.clear();
                    case sf::Keyboard::F:
                        if (!tracer)
                            if (!increaseValue)
                                increaseValue = true;
                            else
                                increaseValue = false;
                        break;
                    default:
                        break;
                }
                if (step <= 0) {
                    stepSize = std::exp(step);
                } else {
                    stepSize = std::max(step * 1 + 1.0, 1.0);
                }
                if (stepSize <= 0.001)
                    step = -6.90;
                size = (size < 5) ? 5 : ((size > 150.0) ? 150.0 : size);

            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Time currentTime = clock.getElapsedTime();
                    lastMousePos = sf::Mouse::getPosition(window);
                    startPoint = window.mapPixelToCoords(lastMousePos); // 초기 클릭 위치 저장
                    if (currentTime - lastClickTime <= sf::seconds(0.2)) {
                        startX = x_scale(startPoint.x, 1 / size);
                        startY = y_scale(startPoint.y, 1 / size);
                    }
                    lastClickTime = currentTime;
                    if (-10000000 <= origin_function_parameter(window, parameter, size, parameter_function, t_value,
                                                               x_scale(startPoint.x, 1 / size),
                                                               y_scale(startPoint.y, 1 / size)))
                        t_value = origin_function_parameter(window, parameter, size, parameter_function, t_value,
                                                            x_scale(startPoint.x, 1 / size),
                                                            y_scale(startPoint.y, 1 / size));
                }
            }

            if ((!tracer) && event.type == sf::Event::MouseMoved) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i newMousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f delta = window.mapPixelToCoords(newMousePos) - window.mapPixelToCoords(lastMousePos);
                    graphView.move(-delta); // 시야 이동
                    window.setView(graphView); // 뷰 설정 업데이트
                    lastMousePos = newMousePos; // 새로운 마우스 위치 저장

                    stepSizeText.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 388);
                    initial_point.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 400);
                    current_t_value.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 376);
                    tracer_on.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 364);
                    error.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 352);
                    error_size.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 338);
                }
            }
        }

        double x_fmod = graphView.getCenter().x - fmod(graphView.getCenter().x, size);
        double y_fmod = graphView.getCenter().y - fmod(graphView.getCenter().y, size);
        double x_start = -600 + fmod(600, size) + x_fmod;
        double x_end = 600 + fmod(600, size) + x_fmod;
        double y_start = -400 + fmod(400, size) + y_fmod;
        double y_end = 400 + fmod(400, size) + y_fmod;
        if (calcul)
            upperbound_error = Error_size(startX, (600 + graphView.getCenter().x) / size, stepSize, differential_function, number);
        else
            upperbound_error = -1;

        stepSizeText.setString("Step Size: " + std::to_string(stepSize));
        initial_point.setString("Initial value: x =" + std::to_string(startX) + ", y =" + std::to_string(startY));
        tracer_on.setString("Tracer mode On");
        current_t_value.setString("t = " + std::to_string(t_value));
        error.setString("x = " + std::to_string(Calculate_error(startX, (600 + graphView.getCenter().x) / size, stepSize)));
        error_size.setString("Error Size: " + std::to_string(upperbound_error));



        // Clear the window
        if (!tracer) {
            window.clear(sf::Color::White);
            window.draw(stepSizeText);
            window.draw(initial_point);
            window.draw(current_t_value);
            window.draw(error);
            window.draw(error_size);
            window.draw(initial_origin_graph);
        } else {
            window.draw(tracer_on);
        }

        origin_function_parameter(window, parameter, size, parameter_function, t_value, x_scale(startPoint.x, 1 / size),
                                  y_scale(startPoint.y, 1 / size));
        origin_function_one(window, origin, size, one_variable_function, x_start, x_end);
        EulerMethod(window, EulerGraph, startX, startY, stepSize, size, differential_function, x_start, x_end, number);
        initial_origin_function_one(window, initial_origin_graph, size, initial_one_variable_function, x_start, x_end, startX, startY, number);

            sf::VertexArray axes(sf::Lines);
        axes.append(sf::Vertex(sf::Vector2f(-(600.0f - graphView.getCenter().x), 0.0f), sf::Color::Black));
        axes.append(sf::Vertex(sf::Vector2f(600.0f + graphView.getCenter().x, 0.0f), sf::Color::Black));
        axes.append(sf::Vertex(sf::Vector2f(0.0f, -400.0f + graphView.getCenter().y), sf::Color::Black));
        axes.append(sf::Vertex(sf::Vector2f(0.0f, 400.0f + graphView.getCenter().y), sf::Color::Black));

        for (double i = x_start; i <= x_end; i += size) {
            axes.append(sf::Vertex(sf::Vector2f(i, -3), sf::Color::Black));
            axes.append(sf::Vertex(sf::Vector2f(i, 3), sf::Color::Black));
        }

        for (double i = y_start; i <= y_end; i += size) {
            axes.append(sf::Vertex(sf::Vector2f(-3, i), sf::Color::Black));
            axes.append(sf::Vertex(sf::Vector2f(3, i), sf::Color::Black));
        }

        window.draw(axes);

        // Display the contents of the window
        window.display();
    }

    return 0;
}