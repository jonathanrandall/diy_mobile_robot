import json
import requests

class BusServoHttp:
    def __init__(self, address):
        self.address = address
        self.session = requests.Session()

    def run_command(self, command, params):
        if params:
            url = f"{self.address}/command?method={command}&params={','.join(map(str, params))}"
        else:
            url = f"{self.address}/command?method={command}"
        try:
            response = self.session.get(url)
            print(response.text)
            response.raise_for_status()
            return response.json() if response.headers['Content-Type'] == 'application/json' else response.text
        except requests.RequestException as e:
            print(f"Request failed: {e}")
            self.session = requests.Session()  # Reopen session if connection fails
            return None

    def run(self, id, p, servo_run_time=1000):
        return self.run_command('run', [id, p, servo_run_time])

    def run_mult(self, pp, servo_run_time):
        return self.run_command('run_mult', [pp, servo_run_time])

    def run_add_or_dec(self, id, speed):
        return self.run_command('run_add_or_dec', [id, speed])

    def stop(self, id):
        return self.run_command('stop', [id])

    def set_ID(self, old_id, new_id):
        return self.run_command('set_ID', [old_id, new_id])

    def get_ID(self, id):
        return self.run_command('get_ID', [id])

    def set_mode(self, id, mode, speed=0):
        return self.run_command('set_mode', [id, mode, speed])

    def load(self, id):
        return self.run_command('load', [id])

    def unload(self, id):
        return self.run_command('unload', [id])

    def servo_receive_handle(self):
        return self.run_command('servo_receive_handle', [])

    def get_position(self, id):
        return int(self.run_command('get_position', [id]))

    def get_positions(self):
        pos_string = self.run_command('get_positions', [])
        try:
            return json.loads(pos_string)
        except json.JSONDecodeError:
            raise Exception(f'Could not get position from string {pos_string}')

    def set_positions(self, goal_positions, servo_run_time):
        assert len(goal_positions) == 6
        self.run_command('set_positions', [*goal_positions, servo_run_time])

    def get_vin(self, id):
        return self.run_command('get_vin', [id])

    def adjust_offset(self, id, offset):
        return self.run_command('adjust_offset', [id, offset])

    def save_offset(self, id):
        return self.run_command('save_offset', [id])

    def get_offset(self, id):
        return self.run_command('get_offset', [id])