using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    public float moveSpeed = 5f;
    public LayerMask collisionLayers; // Layers to collide with
    public float maxDistance = 0.5f; // Maximum distance camera can move before collision

    private void Update()
    {
        // Calculate movement based on input
        float horizontalMovement = Input.GetAxis("Horizontal");
        float verticalMovement = Input.GetAxis("Vertical");

        // Get the camera's current rotation
        Vector3 cameraForward = Camera.main.transform.forward;
        Vector3 cameraRight = Camera.main.transform.right;

        // Calculate the new position using the camera's forward and right vectors
        Vector3 desiredPosition = transform.position + (cameraForward * verticalMovement + cameraRight * horizontalMovement) * moveSpeed * Time.deltaTime;

        // Perform a raycast to check for obstacles
        Vector3 movementDirection = desiredPosition - transform.position;
        RaycastHit hit;
        if (Physics.Raycast(transform.position, movementDirection.normalized, out hit, movementDirection.magnitude + maxDistance, collisionLayers))
        {
            desiredPosition = hit.point - (movementDirection.normalized * maxDistance);
        }

        // Move the object to the new position
        transform.position = desiredPosition;
    }
}
