The format is as follows:
`--` means a beginning of a dialogue state. You can also begin a dialogue state with some arbitrary ID to reference it later.
In the next lines you can write the text of that dialogue stage. This is the text that the NPC will say.
```
--
    This is text said by an NPC
```
or with a stage ID
```
SOME_STAGE_ID
    This is text said by an NPC
```

Then 4 spaces and `-`  marks the beginning of a dialogue option that player can choose
```
--
  some text that NPC says
  - some text that player can say in response
  - some text that player can say in another response
```
if you add `==>` at the and of a dialogue option, you can specify an ID of the next dialogue stage that this option transitions into. If there is no such ID, then the option will transition straight to the dialogue stage below it
```
FIRST_STAGE
    Hello
    - Hi ==> SECOND_STAGE  
    - Bye ==> END_STAGE
SECOND_STAGE
    What's your name?
END_STAGE
    Bye
```
The `==> SECOND_STAGE` is not necessary because `SECOND_STAGE` follows right after `FIRST_STAGE` so you can simpyl write

```
FIRST_STAGE
    Hello
    - Hi 
    - Bye ==> END_STAGE
SECOND_STAGE
    What's your name?
END_STAGE
    Bye
```
You can also use more indentation to structure dialogue branches more in a readable way:

```
FIRST_STAGE
    Hello
    - Hi 
        SECOND_STAGE
            What's your name?
    - Bye ==> END_STAGE
        END_STAGE
            Bye
```
In this case using `==> END_STAGE` is not necessary anymore and can be ommited. So  we don't really need stage IDs anymore so we can also omit writing stage IDs explicitly as well. So a more compact way of writing this is

```
--
    Hello
    - Hi 
        --
            What's your name?
    - Bye 
        --
            Bye
```
If you want to end the dialogue you can transition to `!` stage.
```
--
    Hello
    - Hi 
        --
            What's your name?
    - Bye ==> !
```
It is possible to trigger various functions when user chooses a dialogue option. You simply write the function name after `:`
```
--
    Hello
    - Hi ==>:function1
        --
            What's your name?
    - Bye 
        --
            Bye
```
At the moment there are no functions implemented yet. You can implement your function in blueprints or you can write it directly in text.

You can show certain dialogue options only under certain conditions. The condition function returns a boolean value (true/false)
and can be implemented in blueprints or written directly in text 
```
--
    Hello
    - Hi ==>?conditionFunction1
        --
            What's your name?
    - Bye 
        --
            Bye
```
You can combine `:` adn `?` as follows
```
--
    Hello
    - Hi 
        --
            What's your name?
    - Bye ==>!:functionTriggeredWhenOptionIsChosen ?conditionFunction
```
