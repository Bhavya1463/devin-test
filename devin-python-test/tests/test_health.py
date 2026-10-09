import sys
import os

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from app import app


def test_health_returns_200_ok():
    client = app.test_client()
    response = client.get("/health")
    assert response.status_code == 200


def test_health_returns_json_status_ok():
    client = app.test_client()
    response = client.get("/health")
    assert response.content_type == "application/json"
    assert response.get_json() == {"status": "ok"}
