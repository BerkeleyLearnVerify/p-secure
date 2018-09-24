# Friday Extended Meeting: Monday, 09/21/18
- Emphasized importance of having clean code from the start
- Created a Todoist of all tasks that need to be completed with deadlines
- Again discussed overall architecture of the spark code displayed below (transcribed from whiteboard image):
class BallotBox:
  - addVote: vote -> BallotBox
  - RemoveDup: Ballotox -> BallotBox
class Vote:
  - compareCredential: vote -> bool
  - readCredential: vote -> credential
  - readVote: true -> vote
  - anonVote: true -> vote

- All of the above methods should all other internal methods when approriate
- All class variables and fields should be private
TODOs:
- Clean up Spark code to reflec this architecture
- Read Spark paper
- Read Typestates paper

- This upcoming week we will transition to the P project for the workshop paper
------------------------------------------------
# Monday Extended Meeting: Monday, 09/17/18
- Finish Spark
- Run Pinpong using setup 
- Spawn 2 threads and create pinpong program with zeroMQ and RPC. 
- Look into Binn
- Ping Pong Ding Dong Example
- Try and get Voting System in Programming Enclaves to compile
- Send unbounded array or linked list over ping pong

------------------------------------------------
# Thursday Extended Meeting: Thursday, 09/15/18
- Went over electronic voting system code and were provided with feedback for improvements
- Went over how DAG of spark code fits into the state policy diagrams
- Had P tutorial
- Breifly went over Helio paper and compared it to what we are doing. The difference is Helio paper has only one source. 

TODOs:
- Visualize DAGs, want to see the disassembly
- Refactor code to create minimal DAG, toDf() method becomes problematic since it creates an instance of the DF. We want to create expressions in the form of queries using the most minimal subset. Ideally want to use map and reduce.
------------------------------------------------
# Weekly Friday Meeting: Friday, 09/07/18

- Discussed the electronic voting system and state diagrams for each
- Breifly talked about helio paper. The dataset was directly provided from UCSF, not publicly available. 

Electronic Voting Spec:

- Vote: (credentials: int, id: int, vote: int);
- VotersList: List<credentials>
- BallotBox: List<Vote>

Functions:

1. CastVote: Vote -> bool. 
true: if its a valid voter and legit vote then add it to the BallotBox, false otherwise.
2. RemoveDuplicate: VotersList -> VotersList. 
Removes all the duplicates and picks the latest vote.
3. AnonVote: 
replace the credentials by null.
4. GenerateResults
return the results.
5. CheckVote: BallotBox -> bool

Questions:
Q1: Would you implement it using RDD, DataFrame, Dataset etc. What is the difference in all of them?
Q2: How does spark-submit really work?
Q3: DAG for each of the spark queries.

TODOs:
- Finish spark electronic voting system by Tuesday
- Read Helio Paper

------------------------------------------------

# Meeting with Sanjit: Tuesday, 09/04/18

- Discussed project with Sanjit and gave thumbs up
- Workshop paper deadline in November
- Sign up for units CS199
- Check in biweekly

TODOs:
- Build spark electronic voting system as described earlier
- Experiment with zmq for interaction between different enclaves

------------------------------------------------

# First Project Skype Meeting: Thursday, 08/30/18

Big Project #1
Problem:
Want to ensure that certain types of operations are allowed on that data in certain stages. 
Contains 3 aspects:
- Security Aspect
- Systems building
- Formal Methods and Programming Language

Example: Electronic Voting system with ballot box. Votes have ID, and vote.
Operations: read, counting, compare operation 
- Initially voter can only read vote
- Policy is a state machine: allow read operation only to the voter
- Tabulation teller can read only ID and not vote and perform operation of removing duplicates.
- Anonymize, tabulation teller can perform anonymization operation to allow reading of the vote.
- Throw an exception if behavior deviates from this
- Who can do that operation and what is that operation.
- Ballot box: container add operation by legitimate voters. Counting
- Implemented in Spark
- Contains votes, operation accesses those votes, anonymization 

Policies:
- Can be represented by State machine, logical formulas
- Checked using SAT query, and exhaustive search
- Need to figure out which representation is best
- Modify spark code to evaluate policies
- Run inside enclaves

Short Term, Main Project:
- Write distributed application to run on intel SGX
- P can write programs as state machines
- Extend programming language P:
- Ensure that each state machine runs on a separate intel SGX and data is encrypted
- First do remote attestation

TODOs:
- Install P, run simple examples
- Run and show Intel SGX example
