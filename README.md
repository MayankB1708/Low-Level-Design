# Low-Level Design Problems

This repository contains implementations of various Low-Level Design (LLD) problems in C++, demonstrating the use of common design patterns. 

---

## Table of Contents
1. [Elevator System](#1-elevator-system)
2. [Parking Lot](#2-parking-lot)
3. [Payment Gateway](#3-payment-gateway)
4. [Snake and Food Game](#4-snake-and-food-game)
5. [Tic-Tac-Toe](#5-tic-tac-toe)

---

## 1. Elevator System

### Overview
A multi-elevator system with scheduling capabilities, using Command, Observer, and Strategy patterns.

### Design Patterns Used
- **Command Pattern**: Encapsulates elevator requests as command objects
- **Observer Pattern**:  Notifies displays when elevator state/floor changes
- **Strategy Pattern**: Different scheduling algorithms (FCFS, Scan, Look)

### Class Diagram
```mermaid
classDiagram
    class Direction {
        <<enumeration>>
        UP
        DOWN
        IDLE
    }

    class ElevatorState {
        <<enumeration>>
        IDLE
        MOVING
        STOPPED
        MAINTENANCE
    }

    class Floor {
        -int floorNumber
        +Floor(int num)
        +getFloorNumber() int
    }

    class ElevatorCommand {
        <<interface>>
        +execute()* void
    }

    class ElevatorRequest {
        -int elevatorId
        -int floor
        -bool isInternal
        -Direction direction
        -ElevatorController* controller
        +execute() void
        +getFloor() int
        +getDirection() Direction
        +isInternalRequest() bool
    }

    class ElevatorObserver {
        <<interface>>
        +onElevatorStateChange(int, ElevatorState)* void
        +onElevatorFloorChange(int, int)* void
    }

    class ElevatorDisplay {
        +onElevatorStateChange(int, ElevatorState) void
        +onElevatorFloorChange(int, int) void
    }

    class SchedulingStrategy {
        <<interface>>
        +getNextStop(Elevator*)* int
    }

    class FCFSSchedulingStrategy {
        +getNextStop(Elevator*) int
    }

    class ScanSchedulingStrategy {
        +getNextStop(Elevator*) int
    }

    class LookSchedulingStrategy {
        +getNextStop(Elevator*) int
    }

    class Elevator {
        -int id
        -int currentFloor
        -Direction direction
        -ElevatorState state
        -queue~ElevatorRequest*~ requests
        -vector~ElevatorObserver*~ observers
        +addObserver(ElevatorObserver*) void
        +addRequest(ElevatorRequest*) void
        +getNextRequest() ElevatorRequest*
        +hasRequests() bool
        +moveToNextStop(int) void
    }

    class ElevatorController {
        +processRequest(ElevatorRequest*) void
    }

    ElevatorCommand <|-- ElevatorRequest
    ElevatorObserver <|-- ElevatorDisplay
    SchedulingStrategy <|-- FCFSSchedulingStrategy
    SchedulingStrategy <|-- ScanSchedulingStrategy
    SchedulingStrategy <|-- LookSchedulingStrategy
    Elevator --> ElevatorObserver :  notifies
    Elevator --> ElevatorRequest : processes
    ElevatorRequest --> ElevatorController : uses
```

### Sequence Diagram
```mermaid
sequenceDiagram
    participant User
    participant ElevatorController
    participant ElevatorRequest
    participant Elevator
    participant SchedulingStrategy
    participant ElevatorDisplay

    User->>ElevatorController: Request elevator (floor, direction)
    ElevatorController->>ElevatorRequest: Create request
    ElevatorController->>Elevator: addRequest(request)
    ElevatorController->>SchedulingStrategy: getNextStop(elevator)
    SchedulingStrategy-->>ElevatorController: nextFloor
    ElevatorController->>Elevator: moveToNextStop(nextFloor)
    Elevator->>ElevatorDisplay: onElevatorStateChange(id, MOVING)
    Elevator->>ElevatorDisplay:  onElevatorFloorChange(id, floor)
    Elevator-->>User:  Elevator arrived
```

---

## 2. Parking Lot

### Overview
A parking lot management system with different vehicle types, parking spots, and payment strategies.

### Design Patterns Used
- **Strategy Pattern**: Different fee calculation strategies (Basic, Premium) and payment strategies (Cash, Card)
- **Factory Pattern**: Vehicle creation via VehicleFactory

### Class Diagram
```mermaid
classDiagram
    class ParkingFeeStrategy {
        <<interface>>
        +calculateFee(string, int)* double
    }

    class BasicStrategy {
        +calculateFee(string, int) double
    }

    class PremiumStrategy {
        +calculateFee(string, int) double
    }

    class Vehicle {
        <<abstract>>
        #string license
        #string vehicletype
        #ParkingFeeStrategy* pfs
        +getVehicleType() string
        +getLicensePlate() string
        +calculateFee(int) double
    }

    class Car {
        +Car(string, ParkingFeeStrategy*)
    }

    class Bike {
        +Bike(string, ParkingFeeStrategy*)
    }

    class VehicleFactory {
        +createVehicle(string, string, ParkingFeeStrategy*)$ Vehicle*
    }

    class PaymentStrategy {
        <<interface>>
        +processPayment(double)* void
    }

    class CashPayment {
        +processPayment(double) void
    }

    class CardPayment {
        +processPayment(double) void
    }

    class ParkingSpot {
        <<abstract>>
        #int spotnumber
        #bool occupied
        #Vehicle* vehicle
        #string spottype
        +isOccupied() bool
        +getSpotNumber() int
        +getSpotType() string
        +canParkVehicle(Vehicle*)* bool
        +parkVehicle(Vehicle*) void
        +vacate() void
    }

    class ParkingLot {
        -vector~ParkingSpot*~ spots
        +findAvailableSpot(Vehicle*) ParkingSpot*
        +parkVehicle(Vehicle*) void
        +removeVehicle(string) void
    }

    ParkingFeeStrategy <|-- BasicStrategy
    ParkingFeeStrategy <|-- PremiumStrategy
    Vehicle <|-- Car
    Vehicle <|-- Bike
    Vehicle --> ParkingFeeStrategy : uses
    PaymentStrategy <|-- CashPayment
    PaymentStrategy <|-- CardPayment
    VehicleFactory .. > Vehicle : creates
    ParkingSpot --> Vehicle : contains
    ParkingLot --> ParkingSpot : manages
```

### Sequence Diagram
```mermaid
sequenceDiagram
    participant User
    participant ParkingLot
    participant VehicleFactory
    participant Vehicle
    participant ParkingSpot
    participant ParkingFeeStrategy
    participant PaymentStrategy

    User->>VehicleFactory: createVehicle(type, license, feeStrategy)
    VehicleFactory-->>User: Vehicle
    User->>ParkingLot: findAvailableSpot(vehicle)
    ParkingLot->>ParkingSpot: canParkVehicle(vehicle)
    ParkingSpot-->>ParkingLot: true/false
    ParkingLot-->>User: availableSpot
    User->>ParkingSpot: parkVehicle(vehicle)
    
    Note over User:  After parking duration
    
    User->>Vehicle: calculateFee(hours)
    Vehicle->>ParkingFeeStrategy:  calculateFee(vehicleType, hours)
    ParkingFeeStrategy-->>Vehicle: fee amount
    Vehicle-->>User: fee
    User->>PaymentStrategy: processPayment(fee)
    PaymentStrategy-->>User: Payment confirmed
    User->>ParkingSpot: vacate()
```

---

## 3. Payment Gateway

### Overview
A payment gateway system supporting multiple payment providers with retry mechanisms. 

### Design Patterns Used
- **Strategy Pattern**: Different payment gateways (Razorpay, Stripe)
- **Proxy Pattern**: RetryPaymentProxy for automatic retry on failures
- **Factory Pattern**: GatewayFactory for creating gateway instances
- **Adapter Pattern**: IBankingSystem adapts different bank implementations

### Class Diagram
```mermaid
classDiagram
    class GatewayType {
        <<enumeration>>
        RAZORPAY
        STRIPE
    }

    class PaymentRequest {
        +double amount
        +string userId
        +GatewayType gatewayType
    }

    class PaymentResponse {
        +string transactionId
        +bool isSuccess
    }

    class PaymentGatewayStrategy {
        <<interface>>
        +processPayment(PaymentRequest)* PaymentResponse
    }

    class IBankingSystem {
        <<interface>>
        +executeTransaction(PaymentRequest)* PaymentResponse
    }

    class HDFCBank {
        +executeTransaction(PaymentRequest) PaymentResponse
    }

    class RazorpayGateway {
        -IBankingSystem* bank
        +RazorpayGateway(IBankingSystem*)
        +processPayment(PaymentRequest) PaymentResponse
    }

    class RetryPaymentProxy {
        -PaymentGatewayStrategy* realGateway
        -int maxtries
        +RetryPaymentProxy(PaymentGatewayStrategy*, int)
        +processPayment(PaymentRequest) PaymentResponse
    }

    class GatewayFactory {
        +getGateway(GatewayType, int)$ PaymentGatewayStrategy*
    }

    class PaymentService {
        -PaymentGatewayStrategy* gateway
        +makePayment(PaymentRequest) PaymentResponse
    }

    class PaymentController {
        -PaymentService* service
        +processPayment(PaymentRequest) PaymentResponse
    }

    IBankingSystem <|-- HDFCBank
    PaymentGatewayStrategy <|-- RazorpayGateway
    PaymentGatewayStrategy <|-- RetryPaymentProxy
    RazorpayGateway --> IBankingSystem : uses
    RetryPaymentProxy --> PaymentGatewayStrategy : wraps
    GatewayFactory .. > PaymentGatewayStrategy : creates
    PaymentService --> PaymentGatewayStrategy :  uses
    PaymentController --> PaymentService : uses
```

### Sequence Diagram
```mermaid
sequenceDiagram
    participant Client
    participant PaymentController
    participant PaymentService
    participant GatewayFactory
    participant RetryPaymentProxy
    participant RazorpayGateway
    participant HDFCBank

    Client->>PaymentController: processPayment(request)
    PaymentController->>PaymentService: makePayment(request)
    PaymentService->>GatewayFactory: getGateway(RAZORPAY, 3)
    GatewayFactory->>HDFCBank: new HDFCBank()
    GatewayFactory->>RazorpayGateway:  new RazorpayGateway(bank)
    GatewayFactory->>RetryPaymentProxy: new RetryPaymentProxy(gateway, 3)
    GatewayFactory-->>PaymentService: proxyGateway
    
    loop Retry up to maxTries
        PaymentService->>RetryPaymentProxy:  processPayment(request)
        RetryPaymentProxy->>RazorpayGateway:  processPayment(request)
        RazorpayGateway->>HDFCBank: executeTransaction(request)
        HDFCBank-->>RazorpayGateway: response
        RazorpayGateway-->>RetryPaymentProxy: response
        alt Success
            RetryPaymentProxy-->>PaymentService: successResponse
        else Failure & retries remaining
            Note over RetryPaymentProxy: Retry payment
        end
    end
    
    PaymentService-->>PaymentController: response
    PaymentController-->>Client: response
```

---

## 4. Snake and Food Game

### Overview
Classic snake game implementation with configurable movement strategies.

### Design Patterns Used
- **Strategy Pattern**: Different movement strategies (HumanStrategy for manual control)

### Class Diagram
```mermaid
classDiagram
    class Position {
        +int row
        +int col
        +Position(int, int)
        +operator==(Position) bool
        +operator<(Position) bool
    }

    class GameBoard {
        -int width
        -int height
        +GameBoard(int, int)
        +getWidth() int
        +getHeight() int
    }

    class MovementStrategy {
        <<interface>>
        +getNextPosition(Position, string)* Position
    }

    class HumanStrategy {
        +getNextPosition(Position, string) Position
    }

    class SnakeGame {
        -GameBoard board
        -deque~Position~ snake
        -map~Position, bool~ snakeMap
        -vector~vector~int~~ food
        -int foodIndex
        -MovementStrategy* ms
        +SnakeGame(int, int, vector~vector~int~~)
        +setMovementStrategy(MovementStrategy*) void
        +move(string) int
    }

    MovementStrategy <|-- HumanStrategy
    SnakeGame --> GameBoard : has
    SnakeGame --> MovementStrategy : uses
    SnakeGame --> Position : manages
```

### Sequence Diagram
```mermaid
sequenceDiagram
    participant User
    participant SnakeGame
    participant MovementStrategy
    participant GameBoard

    User->>SnakeGame: new SnakeGame(width, height, foodPositions)
    SnakeGame->>GameBoard: Initialize board
    SnakeGame->>SnakeGame: Initialize snake at (0,0)
    
    loop Game Loop
        User->>SnakeGame: move(direction)
        SnakeGame->>MovementStrategy: getNextPosition(head, direction)
        MovementStrategy-->>SnakeGame: newHead position
        
        alt Out of bounds OR self collision
            SnakeGame-->>User: return -1 (Game Over)
        else Food at newHead
            SnakeGame->>SnakeGame:  Grow snake (don't remove tail)
            SnakeGame->>SnakeGame:  Increment foodIndex
            SnakeGame-->>User: return current score
        else Normal move
            SnakeGame->>SnakeGame: Move snake (add head, remove tail)
            SnakeGame-->>User: return current score
        end
    end
```

---

## 5. Tic-Tac-Toe

### Overview
Tic-Tac-Toe game with configurable player strategies for different input methods.

### Design Patterns Used
- **Strategy Pattern**: Different player strategies (Human, potentially AI)

### Class Diagram
```mermaid
classDiagram
    class Symbol {
        <<enumeration>>
        X
        O
        EMPTY
    }

    class Position {
        +int row
        +int col
        +Position(int, int)
    }

    class PlayerStrategy {
        <<interface>>
        +makeMove(Board&)* Position
    }

    class HumanPlayerStrategy {
        +makeMove(Board&) Position
    }

    class Player {
        -Symbol symbol
        -PlayerStrategy* strategy
        +Player(Symbol, PlayerStrategy*)
        +getSymbol() Symbol
        +getPlayerStrategy() PlayerStrategy*
    }

    class Board {
        -int rows
        -int cols
        -vector~vector~Symbol~~ grid
        +Board(int, int)
        +isValidMove(Position, Symbol) bool
        +makeMove(Position, Symbol) void
        +isWinningLine(Position, Symbol) bool
        +checkWinner() Symbol
        +isFull() bool
    }

    class Game {
        -Board board
        -vector~Player*~ players
        -int currentPlayerIndex
        +startGame() void
        +playTurn() void
        +isGameOver() bool
        +getWinner() Player*
    }

    PlayerStrategy <|-- HumanPlayerStrategy
    Player --> Symbol : has
    Player --> PlayerStrategy : uses
    Board --> Symbol : contains
    Game --> Board : has
    Game --> Player : manages
```

### Sequence Diagram
```mermaid
sequenceDiagram
    participant User
    participant Game
    participant Board
    participant Player
    participant PlayerStrategy

    User->>Game: startGame()
    Game->>Board: Initialize empty board
    Game->>Player: Create players with strategies
    
    loop Until game over
        Game->>Player: getCurrentPlayer()
        Player->>PlayerStrategy: makeMove(board)
        PlayerStrategy-->>Player: position
        Player-->>Game: position
        
        Game->>Board: isValidMove(position, symbol)
        alt Valid move
            Board-->>Game: true
            Game->>Board: makeMove(position, symbol)
            Game->>Board: isWinningLine(position, symbol)
            alt Winner found
                Board-->>Game: true
                Game-->>User: Player wins! 
            else Board full
                Game->>Board: isFull()
                Board-->>Game: true
                Game-->>User: Draw!
            else Continue
                Game->>Game: Switch to next player
            end
        else Invalid move
            Board-->>Game: false
            Game-->>User: Invalid move, try again
        end
    end
```

---
