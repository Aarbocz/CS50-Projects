--Theft took place on July 28, 2020 on Chamberlin Street.

Suspects:
    -- id | name | phone_number | passport_number | license_plate
    686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
Helper:
    864400 | Berthold | (375) 555-8161 |  | 4V16VO0
Location:
    --id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
    36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

-- Find the case from crime_scene_reports
SELECT * FROM crime_scene_reports
    --id | year | month | day | street | description
    295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- Find the three witnesses' interview
SELECT * FROM interviews WHERE day = 28 AND month = 7;

    161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

    162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

    163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Thief left courthouse by car around 10:25
-- Earlier that morning Thief was at ATM on Fifer Street withdrawing money
-- Leaving the court house Thief called someone for less than a minute. They were going to take the earliest flight out tomorrow. The other person purchased the ticket.

-- Check cars who left courthouse 10 min after theft
SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND hour = 10;
    -- id | year | month | day | hour | minute | activity | license_plate
    260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
    261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
    262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
    263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
    264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
    265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
    266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
    267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55

-- Find people who have thise license plates
SELECT * FROM people WHERE license_plate = "5P2BI95" or license_plate = "94KL13X" or license_plate = "6P58WS2" or license_plate = "4328GD8" or license_plate = "G412CB7"or license_plate = "L93JTIZ" or license_plate = "322W7JE"or license_plate = "0NTHK55";
    -- id | name | phone_number | passport_number | license_plate
    221103 | Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
    243696 | Amber | (301) 555-4174 | 7526138472 | 6P58WS2
    396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
    398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
    467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
    514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
    560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
    686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- Find all transactions from the ATM that day
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = "Fifer Street";
    -- id | account_number | year | month | day | atm_location | transaction_type | amount
    246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
    264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
    266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
    267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
    269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
    288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
    313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
    336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35


-- Look for bank accounts that match the ATM transactions and the license plates
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = "Fifer Street") AND person_id IN (SELECT id FROM people WHERE license_plate = "5P2BI95" or license_plate = "94KL13X" or license_plate = "6P58WS2" or license_plate = "4328GD8" or license_plate = "G412CB7"or license_plate = "L93JTIZ" or license_plate = "322W7JE"or license_plate = "0NTHK55");
    -- account_number | person_id | creation_year
    49610011 | 686048 | 2010
    26013199 | 514354 | 2012
    25506511 | 396669 | 2014
    28500762 | 467400 | 2014

-- Return list of suspects after checkin ATM transactions and license plate
SELECT * FROM people where id = 686048 or id = 514354 or id = 396669 or id = 467400;
    id | name | phone_number | passport_number | license_plate
    396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
    467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
    514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
    686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- Look for the call
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60;
    -- id | caller | receiver | year | month | day | duration
    261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
    221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
    254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
    281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54
    233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45 -- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
    224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
    251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
    234 | (609) 555-5876 | (389) 555-5198 | 2020 | 7 | 28 | 60
    255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49 -- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
    279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55

-- Get names info of people who make calls at that time
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60);
    -- id | name | phone_number | passport_number | license_plate
    395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
    398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
    438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
    449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
    514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
    560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
    561160 | Kathryn | (609) 555-5876 | 6121106406 | 4ZY7I8T
    686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
    907148 | Kimberly | (031) 555-6622 | 9628244268 | Q12B3Z3


-- Look for person who suspect called
SELECT * FROM people WHERE phone_number = "(725) 555-3243" OR phone_number = "(375) 555-8161";
    --id | name | phone_number | passport_number | license_plate
    847116 | Philip | (725) 555-3243 | 3391710505 | GW362R6
    864400 | Berthold | (375) 555-8161 |  | 4V16VO0


-- Look for earlliest flight on the 29th
SELECT * FROM flights WHERE day = 29 AND month = 7;
    --id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
    36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

-- Find airport origin and destination
SELECT * FROM airports WHERE id = 8 OR id = 4;
    4 | LHR | Heathrow Airport | London
    8 | CSF | Fiftyville Regional Airport | Fiftyville

-- match flight with suspect passport number
SELECT * FROM passengers WHERE passport_number = 5773159633 OR passport_number = 3592750733;
    -- flight_id | passport_number | seat
    18 | 3592750733 | 4C
    24 | 3592750733 | 2C
    36 | 5773159633 | 4A -- -- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
    54 | 3592750733 | 6C