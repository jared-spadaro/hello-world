import sys

def KaprekarsConstant(num):
    curr = num
    counter = 0
    while curr != 6174:
        temp = str(curr)
        length = len(temp)
        if len(temp) < 4:
            for i in range(4 - length):
                temp = temp + '0'
        curr = int(temp)
        forward = sorted(list(str(curr)))
        reverse = sorted(list(str(curr)), reverse=True)
        forwardInt = int(''.join(forward))
        reverseInt = int(''.join(reverse))
        curr = reverseInt - forwardInt
        print('curr = ' + str(curr))
        counter += 1
    
    # code goes here 
    return counter
    
# keep this function call here  
print (KaprekarsConstant(input()))


  

