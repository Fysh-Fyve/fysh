```mermaid
gantt
    dateFormat  2024-01-02
    title       Project Plan
    excludes    weekends
    %% (`excludes` accepts specific dates in YYYY-MM-DD format, days of the week ("sunday") or "weekends", but not the word "weekdays".)

    section Fysh-Fyve
    Small CPU Components :f51, 2024-01-02, 2w
    Memory f52, after f51

    section FyshSea
    <!-- Describe gantt syntax               :active, a1, after des1, 3d -->
    <!-- Add gantt diagram to demo page      :after a1  , 20h -->
    <!-- Add another diagram to demo page    :doc1, after a1  , 48h -->

    section Digital Aquarium
    <!-- Describe gantt syntax               :after doc1, 3d -->
```
