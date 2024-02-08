# Concept of Operation

The high-level operation of the RISC-V FPGA-based CPU and Language is
illustrated by the following user stories and use cases.

## User Stories

<!-- Maybe have a talk about how my year had 68k? -->
<!-- And only the year after that did we have ARM for assembly -->
<!-- This project is kind of a way for us to keep ECE moving forward to modernity -->

<!-- First instance of tpl. -->
<!-- This is a custom LaTeX command that just turns the text blue and adds brackets. -->
<!-- There should be no instances this command at all before submission. -->

\tpl{Have at most 3 paragraphs per user story, preferably one}

## Use Cases

\tpl{Use UML diagrams and some annotation to present use cases. See this
\href{https://www.youtube.com/watch?v=zid-MVo7M-E&feature=emb_logo}{tutorial}.
Add descriptive text for each use case. Keep the number of use cases below 15; ≤
10 is best. Figure 1 is an example use case diagram, and Table 1 is a Use Case
description table. If a table is complicated, the use case is probably too
low-level}

<!-- PlantUML embed. We use a filter to automatically run PlantUML on these and generate the diagram. -->

```{.plantuml caption="Use Cases <an example use case diagram https://plantuml.com/use-case-diagram>"}
left to right direction
actor "ECE Student" as fc
rectangle Restaurant {
  usecase "Eat Food" as UC1
  usecase "Pay for Food" as UC2
  usecase "Drink" as UC3
}
fc --> UC1
fc --> UC2
fc --> UC3
```

<!-- Insert first use case table. -->

\input{tex/uc-001}
