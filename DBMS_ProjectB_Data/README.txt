Sample Input data:
-----------------------------------
R, Chat, integer, 90
20 lines of multiple insert (separated by ';' with 2~7 key-record pairs): 
200 lines of insert (single key-record)
20 lines of deletion with existed keys

R, Movie, String, 100
20 lines of multiple insert (separated by ';' with 2~7 key-record pairs): 
150 lines of insert (single key-record)
15 lines of deletion with existed keys

Sample Test data:
------------------------------------
Scan Chat
Scan Movie

15 lines of single value index search for "Chat"
15 lines of single value index search for "Movie"

10 lines of range query for "Chat"
10 lines of range query for "Movie"

4 lines of display data page (2 for each relations)

c Chat
c Movie

20 lines of error handling
(8 lines of missing input information, 7 lines of illegal input starting other than <R, I, D, S, q, c, d, p> and 5 lines illegal query)