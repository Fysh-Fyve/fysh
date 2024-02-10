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

The overall system will have two parts as shown in figure \ref{fig:deployment},
the Fysh toolchain in the development machine, and the RISC-V CPU in the Zybo
board.

## System Architecture

<!-- TODO: Remove this and replace with actual text -->

<!-- One or two UML diagrams. Either a UML deployment diagram with component
annotations is appropriate, or separate
\href{https://sparxsystems.com/enterprise_architect_user_guide/15.2/model_domains/deploymentdiagram.html}{deployment}
and
\href{https://sparxsystems.com/enterprise_architect_user_guide/15.2/model_domains/componentdiagram.html}{component}
diagrams.

\vskip 11pt

One or two pages should be needed including a brief text explanation in which
the figure(s) are referenced -->

<!-- In the subsections below, list the major HW, FW, SW subsystems and
components in each. For example, if the design relies on a smartphone, that is
both a deployment node and a HW component. Note any special considerations, such
as specific component or node requirements; e.g., a simple inertial motion unit
may be sufficient for a component that measures motion, or maybe something with
9 degrees of freedom is needed… -->

\input{tex/subsystems}
