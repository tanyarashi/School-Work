﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class weapons : MonoBehaviour
{
   public Transform firePoint;
   public GameObject bulletPrefab;
    // Update is called once per frame
    void Update()
    {
        if(Input.GetButtonDown("Fire1")){
            SoundManagerScript.PlaySound("ShotFired1");
            Shoot();
        }
        
    }
    void Shoot(){
        //shooting logic
        Instantiate(bulletPrefab, firePoint.position, firePoint.rotation);

    }
}
