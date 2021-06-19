import random
import math


def rand(a=0.0, b=1.0):
    return random.random() * (b - a) + a


def restraint(vehicles: list):
    sum_fe = 0.0
    sum_αl = 0.0
    for vehicle in vehicles:
        sum_fe += vehicle.fe
        sum_αl += vehicle.αl
    for vehicle in vehicles:
        vehicle.fe /= sum_fe
        vehicle.αl /= sum_αl


class Vehicle:
    def __init__(self, λ, α, fl, fe, is_random):
        self.λ = λ
        self.fl = fl
        self.fe = fe
        self.αl = α

        if is_random:
            self.I = [1, 2, 3][int(rand(0, 3))]
            self.c = [10, 100, 1000][int(rand(0, 3))]
            self.d = rand(1, 500)
            self.ω = rand(0.4, 0.8)
            self.γ = rand(0.05, 0.2)
            self.N = rand(20, 60)
            self.D = rand(0.1, 1) * 8 * (1024 ** 2)

        else:
            self.I = 2
            self.c = 100
            self.d = 250
            self.ω = 0.6
            self.γ = 0.1
            self.N = 40
            self.D = 0.5 * 8 * (1024 ** 2)

        self.W1 = self.W2 = 1e7
        self.k, self.ke = 1e-27, 1e-29
        self.V = 4
        self.hl = self.hm = 1
        self.ρ = 3e-10
        self.μ = 1.16e-10
        self.𝛎 = 0.5e-10
        self.L = 10 * self.N
        self.M = 10 * self.N
        self.pl = 1
        self.pm = 2
        self.σl = self.σm = 1e-13
        self.ξ = 2.44e-4
        self.θ1 = self.θ2 = 1.5
        self.S = 200
        self.Lmax = 2

    def calculate_R(self):
        R = 0.0
        for i in range(1, int(self.L)):
            division = self.αl * self.pl * self.hl + self.σl * self.d ** self.V
            x = 1.0 + ((self.αl * self.pl * self.hl) / division)
            R0 = (self.W1 / self.L) * math.log(x, 2)
            R += R0
        return R

    def calculate_U(self):
        part1 = self.ξ * self.D

        part2_1 = (self.k * self.c * (1 - self.λ) * self.fl ** 2)
        part2_2 = (self.L * self.pl * self.λ / self.calculate_R())
        part2_3 = self.k * self.c * self.λ * (self.fe) ** 2
        part2 = part2_1 + part2_2 + part2_3

        part3 = self.λ * self.D * (self.μ + self.ν * self.γ + self.ρ * self.c)
        self.U = part1 * part2 + part3
        return self.U

    def self_restraint(self):
        self.tl = (self.c * (1 - self.λ) * self.D) / self.fl
        self.toff = (self.λ * self.D) / self.calculate_R() + (self.c * self.λ * self.D) / self.fe


def optimization(λ, α, fl, fe):
    SCALE = 1
    vehicles = []
    for i in range(SCALE):
        vehicle = Vehicle(λ, α, fl, fe, is_random=True)
        vehicles.append(vehicle)
    restraint(vehicles)
    U = []
    for i in vehicles:
        U.append(i.calculate_U())
    return sum(U) / len(U)
