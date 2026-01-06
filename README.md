**en [ru](README.ru.md)**

###### author: Danila "akshin_" Axyonov

# TransformerCore



### Contents:

1. [Description](#description);
2. [Tools](#tools);
3. [Launch](#launch).



<hr/>



### Description:

**TransformerCore** is a **plug-in for NanoCAD** that implements such a detail as **the core of an electrical transformer** (in simple words: the three-dimensional letter 'E').

This work was created _in the framework of a training practice_ at **IAMCS NR TSU[^1]** together with a partner **Tomsk PI[^2]** (head of practice from the relevant organization/enterprise: Artem Beloshitsky).

**The project implements**:
1. Input of transformer core parameters;
2. Validation of the entered parameters (restrictions are taken from common sense + see the comment to the constructor _TransformerCoreParameters()_);
3. Building a detail with specified parameters in the NanoCAD environment



<hr/>



### Tools:

- .NET 6;
- C#;
- WinForms;
- NanoCAD 24 SDK.



<hr/>



### Launch

1. Assemble the `TransformerCore.View` project (via the usual `dotnet build`, being in the project directory);
2. In the NanoCAD console, type `NETLOAD`;
3. In the Explorer window, select the file `transformer-core -> TransformerCore.View -> bin -> Debug -> net6.0-windows -> TransformerCore.View.dll`;
4. In the NanoCAD console, type `CREATETRANSFORMERCORE`;
5. In the form, enter the requested parameters and click _Готово_;
6. Wait for the drawing to be built in the NanoCAD environment and enjoy.



[^1]: Institute of Applied Mathematics and Computer Science, National Research Tomsk State University.
[^2]: Tomsk Petroleum Institute; currently: **RN Upstream Projecting**.
