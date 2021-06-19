from PSO import PSO
import Vehicle

if __name__ == "__main__":
    pso = PSO(0.8, 400, "Min", 50, 0.2, 2, 2, Vehicle.optimization,
              λ=(0, 1), α=(0, 1), fl=(0, 1.4e9), fe=(0, 3e9))
    pso.run()
