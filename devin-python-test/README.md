# devin-python-test

A minimal Python Flask HTTP service.

## Setup

Install dependencies:

```sh
pip install -r requirements.txt
```

## Run

```sh
python app.py
```

The service listens on `http://localhost:5000`.

## Endpoints

- `GET /health` — returns `200 OK` with JSON body `{"status": "ok"}`.

## Tests

```sh
pytest tests/
```
