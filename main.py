from flask import Flask, Blueprint
from flask_restx import Api

# smart bin api imports
from smart_bin_api import SmartBinAPI
from smart_bin_api import smart_bin_api_ns

blueprint = Blueprint('api', __name__, url_prefix='/api/v1')
app = Flask(__name__)
api_cors_config = {
    'origin' : ['http://localhost:5000']
}
api = Api(blueprint,
          doc='/docs',
          version='1.0.0',
          title='Smart Bin APIs',
          description='These APIs are used to push and pull smart bin data from MongoDB'
          )

# smart bin api
api.add_namespace(smart_bin_api_ns)
smart_bin_api_ns.add_resource(SmartBinAPI, '/')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)

