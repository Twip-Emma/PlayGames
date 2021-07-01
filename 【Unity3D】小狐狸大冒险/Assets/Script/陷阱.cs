using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class 陷阱 : MonoBehaviour
{
    void OnTriggerStay2D(Collider2D other){
        角色移动 pc = other.GetComponent<角色移动>();
        if(pc != null){
            pc.ChangeHealth(-1);
        }
    }
}
