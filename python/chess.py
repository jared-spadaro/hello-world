import math

def chess(str): 
    nums = []
    for i in range(len(str)):
        if str[i].isdigit(): 
            nums.append(int(str[i]))
    x, y, a, b = nums[0], nums[1], nums[2], nums[3]
    return math.factorial((a - x) + (b - y)) / (math.factorial(a - x) * (math.factorial(b - y)))
    
# keep this function call here  
print(chess(input()))  

