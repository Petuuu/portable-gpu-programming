#!/bin/bash
#SBATCH --account=project_2019754
#SBATCH --partition=gpumedium
#SBATCH --gres=gpu:gh200:1
#SBATCH --time=00:01:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=3000M

export NVCOMPILER_ACC_NOTIFY=3

module load nvhpc
nvc -O3 -mp=gpu -gpu=cc90 -Wall axpy.c -o axpy.x

srun ./axpy.x $n
