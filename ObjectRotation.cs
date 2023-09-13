using UnityEngine;

public class ObjectRotation : MonoBehaviour
{
    private bool isRotating = false;
    private float rotationSpeed = 300f;

    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            isRotating = true;
        }
        else if (Input.GetMouseButtonUp(0))
        {
            isRotating = false;
        }

        if (isRotating)
        {
            float rotationAmount = Input.GetAxis("Mouse X") * rotationSpeed * Time.deltaTime;
            transform.Rotate(0f, 0f, rotationAmount);
        }
    }
}

