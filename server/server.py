import os
from flask import Flask, render_template, send_from_directory
import json

app = Flask(__name__)

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/script.js')
def script():
	return render_template('script.js')

@app.route('/style.css')
def style():
	return render_template('style.css')

app.route('/favicon.ico')
def favicon():
	print("Fav icon")
	return send_from_directory(os.path.join(app.root_path, 'static'), 'favicon.ico', mimetype='image/vnd.microsoft.icon')


@app.route('/data')
def data():
	return json.dumps({},indent=0)

if __name__ == '__main__':
	app.run(debug=True, host='0.0.0.0')

