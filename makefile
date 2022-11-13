all:CreateInput CaseResult EquivalenceJudge	
.PHONY:clean

CreateInput:CreateInput.cpp
	g++ -o CreateInput CreateInput.cpp

CaseResult:CaseResult.cpp
	g++ -o CaseResult CaseResult.cpp

EquivalenceJudge:EquivalenceJudge.cpp
	g++ -o EquivalenceJudge EquivalenceJudge.cpp
	
clean:
	rm -f *.o
	rm CreateInput
	rm CaseResult
	rm EquivalenceJudge
