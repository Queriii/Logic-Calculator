#pragma once

constexpr const char* AvailableCommands = 
R"(Yggdrasil.help                          - Displays available commands.
Yggdrasil.table         [Expression]    - Generates truth table corresponding to given expression.
Yggdrasil.tautology     [Expression]    - Checks whether given statement is a tautology.
Yggdrasil.contradiction [Expression]    - Checks whether given statement is a contradiction.
Yggdrasil.argument      [Expr1, ...]    - Checks whether the proposed argument is valid.
)";