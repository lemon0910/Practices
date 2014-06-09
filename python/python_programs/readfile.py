#read a file
filename = raw_input('Enter file name: ')
fd = open(filename, 'r')
for eachLine in fd:
    print eachLine

fd.close()
