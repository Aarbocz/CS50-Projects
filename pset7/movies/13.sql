SELECT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958))))
EXCEPT
SELECT name FROM people WHERE name = "Kevin Bacon";

--SELECT distinct(name) FROM people
--JOIN stars ON people.id = stars.person_id
--JOIN movies ON stars.movie_id = movies.id
--WHERE movies.title IN(SELECT distinct(movies.title) FROM people
--JOIN stars ON people.id = stars.person_id
--JOIN movies ON stars.movie_id = movies.id
--WHERE people.name = "Kevin Bacon" AND people.birth = 1958) AND people.name != "Kevin Bacon";