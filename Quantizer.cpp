// Quantizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include "discpp.h"

//Prototype of uniform_quantization function
double uniform_quantization(double input, double signal_max, double signal_min, double quantizer_length, double step_size);

int main()
{
    //Variables
    double signal_max = 1;
    double signal_min = -1;
    double num_bits = 3;
    double quantizer_len = std::pow(2, num_bits);
    double step_size = std::abs(signal_max - signal_min) / (quantizer_len - 1);
    double input[1024];
    double d_t[1024];
    double error[1024];
    double quantized_input[1024];
    double step = 360.0 / 511;
    Dislin g;
    int ic;
    char cbuf[80];

    //Generating a sine wave
    for (int i = 0; i < 1024; i++) {
        d_t[i] = i * step;
        input[i] = sin(d_t[i]*acos(-1)/180.);
    }

    //Setting Dislin graph
    g.metafl("cons");
    g.scrmod("revers");
    g.disini();
    g.pagera();
    g.complx();
    g.axspos(450, 1800);
    g.axslen(2200, 1200);

    g.name("X-axis", "x");
    g.name("Y-axis", "y");

    g.labdig(-1, "x");
    g.ticks(9, "x");
    g.ticks(10, "y");

    g.titlin("Quantization of a Sine Wave", 1);

    ic = g.intrgb(0.95, 0.95, 0.95);
    g.axsbgd(ic);

    g.graf(0.0, 360.0, 0.0, 90.0, -1.0, 1.0, -1.0, 0.5);
    g.setrgb(0.7, 0.7, 0.7);
    g.grid(1, 1);

    g.color("fore");
    g.height(50);
    g.title();

    g.color("red");
    g.curve(d_t, input, 1024);

    //Quantizing the input
    for (int j = 0; j < 1024; j++) {
        quantized_input[j] = uniform_quantization(input[j], signal_max, signal_min, quantizer_len, step_size);
        error[j] = quantized_input[j] - input[j];
    }

    g.color("blue");
    g.curve(d_t, quantized_input, 1024);

    g.color("green");
    g.curve(d_t, error, 1024);
    
    //Adding a legend to the plot
    g.legini(cbuf, 3, 16);
    g.leglin(cbuf, "Original Signal", 1);
    g.leglin(cbuf, "Quantized Signal", 2);
    g.leglin(cbuf, "Error", 3);
    g.legtit(" ");
    g.legend(cbuf, 7);

    g.disfin();

    return 0;
}

//Implementation of uniform_quantization function
double uniform_quantization(double input, double signal_max, double signal_min, double quantizer_length, double step_size) {
    double quantized_input = 0;
    double signum = (input > 0) - (input < 0);  //Signum function
    
    //Calculating the quantized input
    quantized_input = signum * step_size * std::floor((std::abs(input)/step_size) + 0.5);

    if (input == 1) {
        std::cout << "Input is 1 and quantized value is " << quantized_input << std::endl;
    }

    if (signum == 1 && quantized_input > signal_max) {
        quantized_input = 1;
    }
    else if (signum == -1 && quantized_input < signal_min) {
        quantized_input = -1;
    }

    return quantized_input;
}
