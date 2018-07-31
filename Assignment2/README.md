# Wheel of Fortune  

The show Wheel of Fortune on ABC resembles Hangman, but we won’t have a wheel, Pat Sajak or Vanna White.
In this assignment, you will need to use functionality from `<vector>` and `<string>` .

The following is an execution of the game that you are implement.  
__You should exactly reproduce all prompts and output messages.__  
After the execution run, I will point out certain features to implement.

```
> hangman.exe
You are about to play Hangman.
You will see an underscore in place of every letter within the word
You win if you guess the word, within
        maximum guesses equal to 2 times the letters within the word or a minimum of ten, which ever is larger
        and a time limit of 7 seconds times the letters within the word or a minimum of 40 seconds, which ever is larger

_ _ _ _ _ _
Enter a letter: v
_ _ _ _ _ _
Enter a letter: a
_ _ _ _ _ _
Enter a letter: r
_ _ _ _ _ _
Enter a letter: b
_ b _ _ _ _
Enter a letter: p
_ b _ _ _ _
Enter a letter: n
_ b _ _ _ _
Enter a letter: e
_ b _ e _ _
Enter a letter: l
_ b _ e _ _
Enter a letter: n
n is one of previously guessed letters: varbpnel
Enter a letter: t
_ b _ e _ t
Enter a letter: i
_ b _ e _ t
Enter a letter: o
You exceeded 42 seconds to guess the word
The word was object

Do you want to play again(y/n)? y
_ _ _ _ _ _ _ _
Enter a letter: v
v _ _ _ _ _ _ _
Enter a letter: i
v _ _ i _ _ _ _
Enter a letter: r
v _ r i _ _ _ _
Enter a letter: a
v a r i a _ _ _
Enter a letter: b
v a r i a b _ _
Enter a letter: l
v a r i a b l _
Enter a letter: e
v a r i a b l e
Congratulations! You guessed variable in 7 tries

Do you want to play again(y/n)? y
_ _ _ _ _ _ _ _
Enter a letter: h
_ _ _ _ _ _ _ _
Enter a letter: i
_ _ _ i _ _ _ _
Enter a letter: j
_ _ _ i _ _ _ _
Enter a letter: k
_ _ _ i _ _ _ _
Enter a letter: l
_ _ _ i _ _ l _
Enter a letter: m
_ _ _ i _ _ l _
Enter a letter: n
_ _ _ i _ _ l _
Enter a letter: o
_ _ _ i _ _ l _
Enter a letter: p
_ _ _ i _ _ l _
Enter a letter: q
_ _ _ i _ _ l _
Enter a letter: r
_ _ r i _ _ l _
Enter a letter: s
_ _ r i _ _ l _
Enter a letter: t
_ _ r i _ _ l _
Enter a letter: u
_ _ r i _ _ l _
Enter a letter: v
v _ r i _ _ l _
Enter a letter: w
v _ r i _ _ l _
You exceeded 16 tries.
The word was variable

Do you want to play again(y/n)? m
Do you want to play again(y/n)? x
Do you want to play again(y/n)? n
>
```
----------------------------
Output the multi-line message that precedes the underscores for the first word.

Print out a line having an underscore (_) followed by a space for every letter that is in the secret word.

Ask the user to guess a letter, if that letter appears in the word replace the _ with the letter in all positions containing the letter, and then print out that word showing the properly guessed letters.

The user will get a number of guesses equal to two times the length of the secret word. For instance, if the word was secret, the user will have 12 guesses.

The user will also have a time limit in seconds to guess the word equal to the number of letters times 7.
A call to "time(0)" returns the the number of seconds since 00:00 hours, Jan 1, 1970.
See http://www.cplusplus.com/reference/ctime/time/
Multiple calls to it can be used to check the elapsed time.

If the user repeats a previously guessed letter, a guess is not used up, and you should show the user all letters guessed in that round.

A round should end when the user guesses the word (all underscores have been replaced by a letter) or the number of guesses have been used up or the allowed number of seconds has been exceeded.

When a round has ended, you should ask the user “Do you want to play again? “ 
A response of y results in another round.
A response of n results in the game ending.
A response of any other character causes a re-prompt of whether the user wants another game.

In your main function, seed a random number generator and add the following words to a vector:
```
variable
function
object
expression
plus
pattern
module
debug
integrated
development
environment
virtual
input
shift
constructor
destructor
syntax
iterate
procedure
compiler
Feel free to add additional words to the vector.
```
In main within a loop you will be making calls to the following function that you are being asked to implement:
    `string getSecretWord (const vector &wList);`
where the function is passed the vector of words that you populated, and the function returns a random word from the vector. The string value that is returned will be the word that the user is to guess.

A round is over
  * if the user guessed the word
  * or the time limit has been exceeded
  * or the number of allowed guesses has been execeeded.

Though it is possible that multiple of those events could occur at the same time, it is unlikely.
When a round is over, you should check for the event that ended the round in the order listed above. And, if the user did not guess the word, you should tell him/her what the word was.

__For this and all assignments to follow name the file that you submit should  start with the first letter of your first name, followed by your last name, followed by the assignment number and a ".cpp" suffix. If I was doing this one my file would be named `JGitlin2.cpp`__  

