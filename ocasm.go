package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"strings"
)

func main() {
	if (len(os.Args) != 2) {
		fmt.Printf("Usage: ocasm FILE\n")
		return
	}

	inFilePath := os.Args[1]
	inFile, err := os.Open(inFilePath)
	if err != nil {
		log.Fatalf("%s: %v", inFilePath, err)
	}

	const outFilePath = "out.oca"
	outFile, err := os.Create(outFilePath)
	if err != nil {
		log.Fatalf("%s: %v", outFilePath, err)
	}

	r := bufio.NewReader(inFile)
	for {
		line, _, err := r.ReadLine()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatalf("%s: %v", inFilePath, err)
		}

		parts := strings.SplitN(string(line), " ", 2)
		_, err = fmt.Fprintf(outFile, "%s %s\n", opcode[strings.ToUpper(parts[0])], parts[1])
		if err != nil {
			log.Fatalf("%s: %v", outFilePath, err)
		}
	}
}

var opcode = map[string]string {
	"LD":   "00",
	"LDM":  "01",
	"LDR":  "02",
	"ST":   "10",
	"STD":  "11",
	"NOOP": "EE",
	"HALT": "FF",
}