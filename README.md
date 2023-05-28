# Uniform Quantizer
Quantization is a discretization process in which the continuous range of all possible values of a signal are replaced by a discrete range of values. In other words, a quantizer function $Q:R→Γ$, assigns a value $Q(a)∈Γ$ to each signal value. A formal definition of a quantizer is :

```math
Q(n) = sign(a) * \Delta * \lfloor \frac{|a|}{\Delta} + \frac{1}{2} \rfloor
```

From the equation above, it can be inferred that most of the times quantization simply means to round off or truncate an analog value. This implementation corresponds to a uniform quantizer, which has a quantization step size $(Δ)$ that spaces the quantization levels equally.

In this implementation, a sine signal is simulated and then quantized using the equation above. Dislin (https://www.dislin.de/) is used to plot the result of the quantization process, thus it is necessary to install it in order to run the code.
