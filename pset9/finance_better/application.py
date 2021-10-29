import os

from cs50 import SQL
from datetime import date
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get stocks from portfolio
    portfolio = db.execute("SELECT * FROM portfolio WHERE id = ?", session["user_id"])

    # Delete row if stock quantity = 0
    db.execute("DELETE FROM portfolio WHERE id = ? and quantity = 0", session["user_id"])

    # Get balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    balance = cash[0]['cash']

    # Set variable to calculate balance + stock
    grand_total = balance

    for stock in portfolio:
        # Lookup name of stock
        name = lookup(stock['symbol'])['name']
        # Look up price of stock
        price = lookup(stock['symbol'])['price']
        # Get amount of cash worth for stocks
        total = stock['quantity'] * price

        # Add price, total, and name to each row of portfolio(variable)
        stock.update({'price': usd(price), 'total': usd(total), 'name': name})

        # Add the current stock cash value to balance
        grand_total += total

    # Pass in portfolio variable, balance variable, and grand_total variable to HTML
    return render_template("index.html", stocks=portfolio, balance=usd(balance), total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        # Display buy form
        return render_template("buy.html")

    if request.method == "POST":

        # Get inputs
        quantity = request.form.get("shares")
        symbol = request.form.get("symbol").upper()

        # Shows error if there is no stock symbol or number of shares
        if not symbol:
            message = "Must provide symbol"
            return render_template("buy.html", message=message)

        # Shows error if there is no number of shares
        if not quantity:
            message = "Must provide number"
            return render_template("buy.html", message=message)

        # Check for special character in number input
        if not quantity.isdigit():
            message = "Invalid number"
            return render_template("buy.html", message=message)

        # Ensure number of shares is valid
        if int(quantity) <= 0:
            message = "Number should be bigger than 0"
            return render_template("buy.html", message=message)

        # Look up stocks
        stocks = lookup(symbol)

        # Check is valid stock name provided
        if stocks == None:
            message = "No stock associated with this symbol"
            return render_template("buy.html", message=message)

        # Calculate total cost by stocks
        total = stocks['price'] * int(quantity)

        # Get balance from user account
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        for amount in cash:
            balance = amount["cash"]

        # Check if user has enough money
        new_balance = balance - total
        if new_balance < 0:
            return apology("Sorry")

        # Update user balance
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        # Update transactions table
        db.execute("INSERT INTO transactions VALUES (?, ?, ?, ?, ?, ?, ?, 'BOUGHT')",
                   session["user_id"], stocks['symbol'], stocks['name'], int(quantity), usd(stocks['price']), usd(total), date.today())

        # Update portfolio table
        portfolio = db.execute("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], stocks['symbol'])
        # Create portfolio if there is none
        if not portfolio:
            db.execute("INSERT INTO portfolio VALUES (?, ?, ?)", session["user_id"], stocks['symbol'], int(quantity))
        # Update portfolio
        else:
            old_quantity = db.execute("SELECT quantity FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], stocks['symbol'])
            new_quantity = old_quantity[0]['quantity'] + int(quantity)
            db.execute("UPDATE portfolio SET quantity = ? WHERE id = ? and symbol = ?", new_quantity, session["user_id"], stocks['symbol'])

        # Redirect to homepage
        return redirect("/")

    return apology("Sorry, something went wrong", 500)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE id = ?", session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        # Display quote form
        return render_template("quote.html")

    if request.method == "POST":

        # Get stocks from symbol
        symbol = request.form.get("symbol")
        stocks = lookup(symbol)

        if not stocks:
            # Shows error if there is no stock
            message = "Invalid Symbol"
            return render_template("quote.html", message=message)

        else:
            # Show stock
            message = f"A share of {stocks['name']} ({stocks['symbol']}) costs {usd(stocks['price'])}."
            return render_template("quote.html", message=message)

    return apology("Sorry, something went wrong", 500)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "GET":
        # Display registration form
        return render_template("register.html")

    if request.method == "POST":

        # Get username and password from form input field
        username = request.form.get("username")
        password = request.form.get("password")

        # Check input fields were completed correctly
        if not username:
            return apology("missing username", 400)

        elif not password:
            return apology("missing password", 400)

        elif not password == request.form.get("confirmation"):
            return apology("passwords does not match", 400)

        # Check if username already exists
        users = db.execute("SELECT username FROM users")
        for user in users:
            if (user["username"] == username):
                return apology("username already exists", 400)

        # Hash password
        hash = generate_password_hash(password)

        # Insert new user into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Log user in:
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    return apology("Sorry, something went wrong", 500)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":
        symbols = db.execute("SELECT symbol FROM portfolio WHERE id = ?", session["user_id"])
        return render_template("sell.html", symbols=symbols)

    if request.method == "POST":

        # Get input from form
        symbol = request.form.get("symbol")
        quantity = request.form.get("shares")

        # Handle error if user does not select symbol
        if not symbol:
            return apology("Must provide symbol")

        # Handle error if user does not select quantity
        if not quantity:
            return apology("Must provide number of stocks")

        # Handle error if quantity is not whole numbers
        if not quantity.isdigit():
            return apology("Invalid number")

        if int(quantity) <= 0:
            return apology("Number should be bigger than 0")

        # Get stocks quantity from portfoli
        owned_stock = db.execute("SELECT quantity FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], symbol)

        # Check if user has the stock
        if not owned_stock:
            return apology("You don't own any stocks associated with this symbol")

         # Check if the user has enough stocks to sell
        if owned_stock[0]['quantity'] < int(quantity):
            return apology("You don't have this many stocks to sell")

        # Look up stock current price
        stocks = lookup(symbol)

        # Calculate total selling price
        total = stocks['price'] * int(quantity)

        # Update users balance
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        new_balance = current_balance[0]['cash'] + total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        # Update portfolio
        new_quantity = owned_stock[0]['quantity'] - int(quantity)
        db.execute("UPDATE portfolio SET quantity = ? WHERE id = ? AND symbol = ?", new_quantity, session["user_id"], symbol)

        # Update transaction
        db.execute("INSERT INTO transactions VALUES (?, ?, ?, ?, ?, ?, ?, 'SOLD')",
                   session["user_id"], stocks['symbol'], stocks['name'], int(quantity), usd(stocks['price']), usd(total), date.today())

        return redirect("/")

    return apology("Sorry, something went wrong", 500)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
