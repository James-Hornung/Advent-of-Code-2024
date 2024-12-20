FILENAME = "input.txt"


def is_safe(num1, num2, incr):
    safe = True
    if incr and num1 > num2:
        safe = False
    if not incr and num1 < num2:
        safe = False
    if num1 == num2:
        safe = False
    diff = abs(num1 - num2)
    if diff > 3:
        safe = False
    
    return safe


def read_file():

    with open(FILENAME) as f:
        lines = f.readlines()


    for i in range(len(lines)):
        lines[i] = lines[i].split()
        for j in range(len(lines[i])):
            lines[i][j] = int(lines[i][j])
    
    return lines

def part1():
    lines = read_file()

    count = 0

    for line in lines:
        safe = True

        if line[0] < line[1]:
            incr = True
        else:
            incr = False

        for i in range(len(line) - 1):
            safe = safe and is_safe(line[i], line[i + 1], incr)
        if safe:
            count += 1
    
    return count


def deep_copy(arr):
    new_arr = []
    for element in arr:
        new_arr.append(element)
    
    return new_arr

def part2():
    lines = read_file()

    count = 0

    for line in lines:
        for j in range(len(line)):
            sub_line = deep_copy(line)
            sub_line.pop(j)
            safe = True

            if sub_line[0] < sub_line[1]:
                incr = True
            else:
                incr = False

            for i in range(len(sub_line) - 1):
                safe = safe and is_safe(sub_line[i], sub_line[i + 1], incr)
            if safe:
                count += 1
                break
    
    return count

def main():
    print("Part1 ans:", part1())
    print("Part2 ans:", part2())

if __name__ == "__main__":
    main()
