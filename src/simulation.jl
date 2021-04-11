# ~~~~~~~~~~~~~~~~~
# declare constants
# ~~~~~~~~~~~~~~~~~

# arena size (cm)
const ARENA = (x=100, y=100)

# goal-line coordinates
const GOAL = (left=(x=40, y=100), right=(x=60, y=100))

# assume circular robot (cm)
const ROBOT_RADIUS = 19

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
    function Robot()
        # TODO
    end
end

# Ball represents the position and motion of the ball
mutable struct Ball
    p::XYVector # position
    v::XYVector # velocity
    a::XYVector # acceleration
end

# Simulation serves as entry point to updating states
struct Simulation
    robots::AbstractVector{Robot}
    ball::Ball
    Δt::AbstractFloat

    function Simulation(n_robots::Integer, Δt::Float)
        robots = [Robot(i) for i ∈ 1:n_robots]
        # TODO
    end
end

# ~~~~~~~~~~~~~~~~~
# declare functions
# ~~~~~~~~~~~~~~~~~

# should trigger a single timestep of the system (probably in another function)
function send_commands!(sim::Simulation, commands)
    # TODO
end

# should compile all the key signal data into one data structure
# add noise, too
function get_signals(sim::Simulation)
    # TODO
end
