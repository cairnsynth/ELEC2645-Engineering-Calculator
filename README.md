# Engineering Calculator

This was created for the ELEC2645 Unit 2 group project, in which each team member is tasked with creating a function for an engineering calculator. It has three main features:

 - Inverting Amplifier Calculator
 - Filter Calculator
 - Resistor Colour Code Calculator

 ### Inverting Amplifier Calculator

This section of the application allows users to design Op-Amp based inverting amplifier circuits. The user enters a series of specifications such as gain, input impedance, and is then presented with the appropriate component values to use in the circuit.

Component values are automatically rounded to the E12 series of component values to allow for easy translation into a physical circuit.

Further functions of the amplifier designer include:
- Overview of calculations
- Saving of specifications and values to a file
- Generating a circuit diagram in the form of a Falstad Circuit Simulator file
- Simulating signals passing through the circuit, including visualisation of output saturation, with use of a built in signal emulator

Planned features include:
- Comparison of different Op-Amps and their suitablilty in the designed circuit
- Simulations of the circuit using specific Op-Amps, to show gain characteristics and saturation levels of each IC
