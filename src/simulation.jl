# ~~~~~~~~~~~~~~~
# declare structs
# ~~~~~~~~~~~~~~~

# XYVector represents a vector in the XY plane
# can represent position, velocity, or acceleration
mutable struct XYVector
    x::AbstractFloat
    y::AbstractFloat
end

# USVector represents the signals from every ultrasonic sensor
# can represent distances, velocities, or accelerations
mutable struct USVector
    FC::AbstractFloat # front center
    FL::AbstractFloat # front left
    FR::AbstractFloat # front right
    BC::AbstractFloat # back center
    BL::AbstractFloat # back left
    BR::AbstractFloat # back right

    # zero-initialize upon construction
    function USVector()
        return new(0,0,0,0,0,0)
    end
end

# Robot represents a single robot and the current state of its signals
mutable struct Robot
    id::Integer # robot ID

    # IMU
    p::XYVector # position
    v::XYVector # velocity
    a::XYVector # acceleration
    θ::AbstractFloat # angular position
    ω::AbstractFloat # angular velocity
    α::AbstractFloat # angular acceleration

    # US sensors
    d::USVector # ultrasonic distances
    Δd::USVector # ultrasonic velocities
    ΔΔd::USVector # ultrasonic accelerations

    # zero-initialize except id
    function Robot(id::Integer, p::XYVector)
        v = XYVector(0, 0)
        a = XYVector(0, 0)
        d = USVector()
        Δd = USVector()
        ΔΔd = USVector()
        return new(id, p, v, a, 0, 0, 0, d, Δd, ΔΔd)
    end
end

# Ball represents the position and motion of the ball
mutable struct Ball
    p::XYVector # position
    v::XYVector # velocity
    a::XYVector # acceleration

    function Ball(p::XYVector)
        return new(p, 0, 0)
    end
end

# Simulation serves as entry point to updating states
struct Simulation
    robots::AbstractVector{Robot}
    ball::Ball
    Δt::AbstractFloat

    function Simulation(n_robots::Integer, start_positions::AbstractVector{XYVector}, Δt::AbstractFloat)
        robots = [Robot(i, start_positions[i]) for i ∈ 1:n_robots]
        return new(robots, Ball(XYVector(50, 50)), Δt)
    end
end

# ~~~~~~~~~~~~
# declare enum
# ~~~~~~~~~~~~

@enum COMMANDS begin
    GO_FORWARD = 1
    TURN_LEFT = 2
    TURN_RIGHT = 3
    GO_BACKWARD = 4
end

# ~~~~~~~~~~~~~~~~~
# declare constants
# ~~~~~~~~~~~~~~~~~

# arena size (cm)
const ARENA = (x=100, y=100)

# goal-line coordinates
const GOAL = (left=XYVector(40, 100), right=XYVector(60, 100))

# assume circular robot (cm)
const ROBOT_RADIUS = 19

# ball radius (cm)
const BALL_RADIUS = 8

# ~~~~~~~~~~~~~~~~~
# declare functions
# ~~~~~~~~~~~~~~~~~

function distance(a::XYVector, b::XYVector)::AbstractFloat
    return √((a.x - b.x)^2 + (a.y - b.y)^2)
end

function update_robot!(robot::Robot, sim::Simulation, command::COMMANDS)
    # TODO
end

# should trigger a single timestep of the system (probably in another function)
function send_commands!(sim::Simulation, commands::Dict{Integer,COMMANDS})
    # TODO
    # update every robot
end

# should compile all the key signal data into one data structure
# add noise, too
function get_signals(sim::Simulation)
    # TODO
end
