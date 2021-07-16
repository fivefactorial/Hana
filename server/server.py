from flask import Flask
import json

app = Flask(__name__)

@app.route('/')
def index():
	try:
		return open('index.html').read()
	except:
		return "", 404

@app.route('/script.js')
def script():
	try:
		return open('script.js').read()
	except:
		return "", 404

@app.route('/style.css')
def style():
	return open('style.css').read()



@app.route('/data')
def data():
	return json.dumps({},indent=0)

if __name__ == '__main__':
	app.run(debug=True, host='0.0.0.0')

