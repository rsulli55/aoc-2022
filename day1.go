package main

import (
    "bufio"
    "fmt"
    "log"
    "sort"
    "strconv"
    "os"
)

func main() {
    f, err := os.Open("input_day1")
    if err != nil {
        log.Fatal(err)
    }
    defer f.Close()

    scanner := bufio.NewScanner(f)
    
    var currentSum uint32 = 0
    var elfSums []uint32


    for scanner.Scan() {
        line := scanner.Text()
        if (len(line) == 0) {
            elfSums = append(elfSums, currentSum)
            currentSum = 0
        } else {
            i, err := strconv.ParseUint(line, 10, 32)
            if err != nil {
                log.Fatal(err)
                panic(err)
            }
            currentSum += uint32(i)
        }
    }

    sort.Slice(elfSums, func(i, j int) bool {
            return elfSums[i] > elfSums[j]
        })

    fmt.Println("Top elf:", elfSums[0])
    fmt.Println("Top three sum:", elfSums[0] + elfSums[1] + elfSums[2])

}

