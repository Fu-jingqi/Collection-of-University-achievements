# coding=gbk
import random
import math
import numpy as np
import matplotlib.pyplot as plt

population_size = 1000  # ��Ⱥ��
generations = 300  # ���� ������������
chrom_length = 10  # Ⱦɫ�峤
pc = 0.6  # �������
pm = 0.01  # �������
genetic_population = []  # �������
population = []  # ��Ⱥ��Ӧֵ ����������� ��Χ[0,10] ��Ϊ���ǽ�����ֵ��Ϊ��Ӧ�ȣ�ֻ��Ҫ��ϵ�Ա������˴��ȼ����Ա�����ֵ
fitness = []  # ��Ӧ��
fitness_mean = []  # ƽ����Ӧ�ȣ�����Ⱥ��������ֵ
optimum_solution = []  # ÿ�ε����Ž�


# Ⱦɫ����� ���ɶ�����Ⱦɫ�� ������Ⱥ
# �ֱ�Ե�i��������� �������������������֮��
def chrom_encoding():
    for i in range(population_size):
        population_i = []  # ��Ⱥ�е�i������
        for j in range(chrom_length):
            population_i.append(random.randint(0, 1))
        genetic_population.append(population_i)


# ������ ת ʮ����  ����Ϊ��Ⱦɫ����н���
def chrom_decoding():
    population.clear()
    for i in range(population_size):
        val = 0
        for j in range(chrom_length):
            val += genetic_population[i][j] * (2 ** (chrom_length - 1 - j))
        population.append(val * 10 / (2 ** (chrom_length) - 1))  # �Խ���ֵ���б�׼��ʹ֮����ֲ���[0,10]


# ��Ӧ�ȼ���
def calc_fitness():
    sum = 0.0
    fitness.clear()
    for i in range(population_size):
        func_val = 10 * math.sin(5 * population[i]) + 7 * math.cos(4 * population[i])

        if func_val > 0.0:
            sum += func_val
            fitness.append(func_val)
        else:
            fitness.append(0.0)  # ��Ϊcase2 ��ȫ����Ӧ
    return sum / population_size  # ƽ����Ӧ��


# �õ����Ÿ���
def best_val():
    max_fitness = fitness[0]
    max_id = 0
    for i in range(population_size):
        if max_fitness < fitness[i]:
            max_fitness = fitness[i]
            max_id = i
    return max_fitness, max_id


# ���̶�
def selection():
    tmp = np.array(fitness)
    new_population_id = np.random.choice(np.arange(population_size), population_size, replace=True, p=tmp / tmp.sum())
    new_genetic_population = []
    global genetic_population
    for i in range(population_size):
        new_genetic_population.append(genetic_population[new_population_id[i]])
    genetic_population = new_genetic_population


# ����
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


# ����
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
plt.xlabel('��������', fontproperties='SimHei')
plt.ylabel('���Ž�', fontproperties='SimHei')

fig2 = plt.figure(2)
plt.plot(range(1, generations + 1), fitness_mean)
plt.xlabel('��������', fontproperties='SimHei')
plt.ylabel('ƽ����Ӧ��', fontproperties='SimHei')
plt.show()
