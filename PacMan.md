# Pacman
# Logic

### Entities

```mermaid
classDiagram
    Entity <|-- DynamicEntity
        DynamicEntity <|-- Pacman
        DynamicEntity <|-- Ghost
    Entity <|-- CollectableEntity
        CollectableEntity <|-- Coin
        CollectableEntity <|-- PowerUp
```

# Game States

The State System uses a stack-based StateManager to handle game flow transitions, where each state (Menu, Level, Pause, Victory, GameOver) manages its own transitions by pushing/popping new state objects onto the stack while maintaining clear separation between game logic and representation.

States control their own transitions and lifecycle, with LevelState creating fresh World instances for each level while persistent game data like score and lives is managed externally through observer systems.
```mermaid
stateDiagram-v2
    direction LR
    [*] --> MenuState
    
    MenuState --> LevelState : Start
    LevelState --> PausedState : Pause
    PausedState --> LevelState : Resume
    LevelState --> VictoryState : All Coins
    LevelState --> GameOverState : No Lives
    PausedState --> . : Quit to Menu
    VictoryState --> LevelState : New Level
    GameOverState --> LevelState : Restart
    VictoryState --> . : Quit to Menu
    GameOverState --> . : Quit to Menu
    . --> MenuState : Quit to Menu
```
# Factory
```mermaid
sequenceDiagram
participant F as ConcreteFactory
participant M as PacManModel (Subject)
participant V as PacManView (Observer)
participant S as Score (Observer)

         %% 1. Object Creation & Subscription
         F->>+M: Creates PacManModel
         F->>+V: Creates PacManView
        F->>+S: Creates Score
   
        Note over F,M: Factory subscribes Observers to the Subject.
        F->>M: attach(pacManView)
        F->>M: attach(score)
        deactivate M
        deactivate V
        deactivate S
    
        %% 2. Game Event and Notification
        participant G as GameLoop
        Note over G,S: ... some time later, in the game loop ...
    
        G->>+M: move() // State changes in the Subject
        
        Note right of M: Subject decides to notify its observers.
        M->>M: notify()
    
        M->>+V: update()
        Note right of V: View gets new data from Model and redraws.
        V->>V: draw()
        V-->>-M: 
        
        M->>+S: onNotify()
        Note right of S: Score updates its value.
        S->>S: updateScore()

```