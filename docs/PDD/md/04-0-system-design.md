# System Design

<!-- TODO: Remove this and replace with actual text -->

<!-- Define the system architecture that will meet the FRs and PRs. Think of
deployment first (are there separate physical parts, like a smartphone and
remote sensor?), and then for each deployment element, define the main HW, SW,
and FW components and their relationship. A UML deployment diagram with
component annotations is appropriate, or separate
\href{https://sparxsystems.com/enterprise_architect_user_guide/15.2/model_domains/deploymentdiagram.html}{deployment}
and
\href{https://sparxsystems.com/enterprise_architect_user_guide/15.2/model_domains/componentdiagram.html}{component}
diagrams. -->

<!-- \vskip 11pt -->

<!-- Here, one introductory paragraph is required and expected. It should describe
the system at a very high level. E.g., “The Toddler Monitor system comprises two
main subsystem, the user’s smartphone and the monitor. Major nodes and
components in each subsystem are identified below”. -->

The overall system will have two parts as shown in Figure \ref{fig:deployment},
the Fysh toolchain in the development machine, and the RISC-V CPU in the
Programmable Logic (PL) of the Zybo board. The development machine is usually
not part of the "deployment", but the compiler is part of the project and should
be shown in this case.

## System Architecture

\input{tex/subsystems}
