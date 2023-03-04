with open ('./programs/program_4.txt','r') as fil:
    data = fil.read()
    data = data.split('\n')
    for i in range(len(data)):
        data[i] = data[i].split(" ")

data = data[:-1]
print(len(data))


stalling = 0

def IFFunction(executionCycle, stalling):
    myIndex = 0
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    return stalling

def IDFunction(executionCycle, stalling):
    myIndex = 1
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = IFFunction(executionCycle, stalling)
    return stalling

def IAFunction(executionCycle, stalling):
    myIndex = 2
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = IDFunction(executionCycle, stalling)
    return stalling

def RRFunction(executionCycle, stalling):
    myIndex = 3
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = IAFunction(executionCycle, stalling)
    return stalling

def ADDFunction(executionCycle, stalling):
    myIndex = 4
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = RRFunction(executionCycle, stalling)
    return stalling

def MULFunction(executionCycle, stalling):
    myIndex = 5
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = ADDFunction(executionCycle, stalling)
    return stalling

def DIVFunction(executionCycle, stalling):
    myIndex = 6
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = MULFunction(executionCycle, stalling)
    return stalling

def BRFunction(executionCycle, stalling):
    myIndex = 7
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = DIVFunction(executionCycle, stalling)
    return stalling

def Mem1Function(executionCycle, stalling):
    myIndex = 8
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = BRFunction(executionCycle, stalling)
    return stalling

def Mem2Function(executionCycle, stalling):
    myIndex = 9
    if executionCycle[myIndex] != 0 and data[executionCycle[myIndex]-1][1] == "ld":
        stalling = True
    # elif executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = Mem1Function(executionCycle, stalling)
    return stalling

def WBFunction(executionCycle, stalling):
    myIndex = 10
    # if executionCycle[myIndex] != 0:
        # print(" ".join(data[executionCycle[myIndex]-1]))
    stalling = Mem2Function(executionCycle, stalling)
    return stalling


def pipelining(totalInstructions, stalling):
    executionCycle = [0]*11
    counter = 0
    temp = 1
    print(executionCycle)
    while executionCycle[-1]!= totalInstructions:
        for j in range(len(executionCycle)-1,-1,-1):
            executionCycle[j] = executionCycle[j-1]
            if j==0:
                if stalling == 0:
                    if temp == totalInstructions+1:
                        executionCycle[j] = 0
                    else:
                        executionCycle[j] = temp
                        temp += 1
                else:
                    stalling = False
                    executionCycle[j] = 0
        stalling = WBFunction(executionCycle, stalling)
        print()
        print(executionCycle)
        counter += 1

    # executionCycle[-1] = 0
    # print(executionCycle)
    # print(counter)

pipelining(totalInstructions=len(data), stalling=False)