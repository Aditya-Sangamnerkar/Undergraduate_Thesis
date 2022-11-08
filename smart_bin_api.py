from flask_restx import Resource, Namespace, fields
from flask import request, jsonify

# create namespace for the api
smart_bin_api_ns = Namespace('smart_bin_api', description='DB Operations for smart bin api')

smart_bin_post_api_details = smart_bin_api_ns.model('create operation for DB', {})


class SmartBinAPI(Resource):

    @smart_bin_api_ns.expect(smart_bin_post_api_details)
    def post(self):
        pass

    def get(self):
        pass

