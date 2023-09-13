using UnityEngine;

public class CameraRotation : MonoBehaviour
{
    public float rotationSpeed = 0.25f;
    public Transform target;
    public float verticalRotationLimit = 360f;

    private bool isRotating = false;
    private Vector3 lastMousePosition;

    void Update()
    {
        if (Input.GetMouseButtonDown(1))
        {
            isRotating = true;
            lastMousePosition = Input.mousePosition;
        }

        if (Input.GetMouseButtonUp(1))
        {
            isRotating = false;
        }

        if (isRotating)
        {
            Vector3 currentMousePosition = Input.mousePosition;
            Vector3 mouseDelta = currentMousePosition - lastMousePosition;

            float rotateAroundVerticalAxis = -mouseDelta.y * rotationSpeed;
            float rotateAroundHorizontalAxis = mouseDelta.x * rotationSpeed;

            Vector3 currentRotation = transform.localEulerAngles;

            float newVerticalRotation = currentRotation.x + rotateAroundVerticalAxis;
            float newHorizontalRotation = currentRotation.y + rotateAroundHorizontalAxis;

            // Clamp vertical rotation within the specified limits
            newVerticalRotation = Mathf.Clamp(newVerticalRotation, -verticalRotationLimit, verticalRotationLimit);

            transform.localEulerAngles = new Vector3(newVerticalRotation, newHorizontalRotation, 0);

            lastMousePosition = currentMousePosition;
        }
    }
}

