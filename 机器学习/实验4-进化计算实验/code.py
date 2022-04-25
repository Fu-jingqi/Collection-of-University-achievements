# coding=gbk
import random
import math
import numpy as np
import matplotlib.pyplot as plt

population_size = 1000  # 种群数
generations = 300  # 代数 （迭代次数）
chrom_length = 10  # 染色体长
pc = 0.6  # 交配概率
pm = 0.01  # 变异概率
genetic_population = []  # 基因编码
population = []  # 种群对应值 即基因表现型 范围[0,10] 因为我们将函数值作为适应度，只需要关系自变量，此处等价于自变量的值
fitness = []  # 适应度
fitness_mean = []  # 平均适应度，即种群最后的收敛值
optimum_solution = []  # 每次的最优解


# 染色体编码 生成二进制染色体 生成种群
# 分别对第i个个体编码 并将其放入基因编码序列之中
def chrom_encoding():
    for i in range(population_size):
        population_i = []  # 种群中第i个物种
        for j in range(chrom_length):
            population_i.append(random.randint(0, 1))
        genetic_population.append(population_i)


# 二进制 转 十进制  作用为对染色体进行解码
def chrom_decoding():
    population.clear()
    for i in range(population_size):
        val = 0
        for j in range(chrom_length):
            val += genetic_population[i][j] * (2 ** (chrom_length - 1 - j))
        population.append(val * 10 / (2 ** (chrom_length) - 1))  # 对解码值进行标准化使之区间分布在[0,10]


# 适应度计算
def calc_fitness():
    sum = 0.0
    fitness.clear()
    for i in range(population_size):
        func_val = 10 * math.sin(5 * population[i]) + 7 * math.cos(4 * population[i])

        if func_val > 0.0:
            sum += func_val
            fitness.append(func_val)
        else:
            fitness.append(0.0)  # 认为case2 完全不适应
    return sum / population_size  # 平均适应度


# 得到最优个体
def best_val():
    max_fitness = fitness[0]
    max_id = 0
    for i in range(population_size):
        if max_fitness < fitness[i]:
            max_fitness = fitness[i]
            max_id = i
    return max_fitness, max_id


# 轮盘赌
def selection():
    tmp = np.array(fitness)
    new_population_id = np.random.choice(np.arange(population_size), population_size, replace=True, p=tmp / tmp.sum())
    new_genetic_population = []
    global genetic_population
    for i in range(population_size):
        new_genetic_population.append(genetic_population[new_population_id[i]])
    genetic_population = new_genetic_population


# 交配
def crossover():
    for i in range(0, population_size - 1, 2):
        if random.random() < pc:
            change_point = random.randint(0, chrom_length - 1)
            tmp1 = []
            tmp2 = []
            tmp1.extend(genetic_population[i][0:change_point])
            tmp1.extend(genetic_population[i + 1][change_point:])
            tmp2.extend(genetic_population[i + 1][0:change_point])
            tmp2.extend(genetic_population[i][change_point:])
            genetic_population[i] = tmp1
            genetic_population[i + 1] = tmp2


# 变异
def mutation():
    for i in range(population_size):
        if random.random() < pm:
            mutation_point = random.randint(0, chrom_length - 1)
            genetic_population[i][mutation_point] ^= 1


chrom_encoding()
for stp in range(generations):
    chrom_decoding()
    fit_mean = calc_fitness()
    best_fitness, best_id = best_val()
    optimum_solution.append(best_fitness)
    fitness_mean.append(fit_mean)
    selection()
    crossover()
    mutation()

fig1 = plt.figure(1)
plt.plot(range(1, generations + 1), optimum_solution)
plt.xlabel('迭代次数', fontproperties='SimHei')
plt.ylabel('最优解', fontproperties='SimHei')

fig2 = plt.figure(2)
plt.plot(range(1, generations + 1), fitness_mean)
plt.xlabel('迭代次数', fontproperties='SimHei')
plt.ylabel('平均适应度', fontproperties='SimHei')
plt.show()
